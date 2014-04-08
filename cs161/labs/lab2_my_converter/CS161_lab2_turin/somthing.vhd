library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity read_fsm_1in is
  generic( 
    CISE_WIDTH_IN : natural := 32;
    OPERATOR_WIDTH_IN : natural := 64;
    NUMBER_OF_INPUT_WORDS_IN : natural := 2
    );
  port 
    (
      FSL_Clk : in	std_logic;
      FSL_Rst : in	std_logic;
      FSL_S_Read : out	std_logic;
      FSL_S_Data : in	std_logic_vector(CISE_WIDTH_IN-1 downto 0);
      FSL_S_Exists : in	std_logic;
		FSL_S_Control : in std_logic;
      LHSData : out	std_logic_vector(OPERATOR_WIDTH_IN-1 downto 0);
      Valid : out std_logic
      );
end read_fsm_1in;

--VHDL convention:
--Using to interface indicating bit 0 as the MSB and 

architecture CISE of read_fsm_1in is
-- Signal and variable section
-- Signal convention <name>_i, represents next value
-- Signal convention <name>_o, represents current value
  --Sample Signal
  --signal output_i, output_o : std_logic := '0';

  -- Total number of input data.
  constant NUMBER_OF_INPUT_WORDS : natural := NUMBER_OF_INPUT_WORDS_IN;
  -- Data input width of the operator
  constant OPERATOR_WIDTH : natural := OPERATOR_WIDTH_IN;
  --Width of the CISE interface
  constant CISE_WIDTH : natural := CISE_WIDTH_IN;

  -- Counters to store the number inputs reads
  signal nr_of_reads_i, nr_of_reads_o : natural range 0 to NUMBER_OF_INPUT_WORDS-1;

  --States for state machine in enumerated form
  type FSM_RD_STATE_TYPE is (Read_LHS_Upper, Read_LHS_Lower, 
                             Read_RHS_Upper, Read_RHS_Lower);
  signal fsm_rd_state_i, fsm_rd_state_o : FSM_RD_STATE_TYPE;

--Register lines
  --Computation is valid flag
  signal ram_valid_i, ram_valid_o : std_logic := '0';

  --Input operatorator register
  signal ram_lhs_i, ram_lhs_o : std_logic_vector(OPERATOR_WIDTH-1 downto 0) := (others => '0');

  --Sync 32bit words to 64 bit word intermediate registers
  signal ram_lhs_upper_i : std_logic_vector(CISE_WIDTH-1 downto 0) := (others => '0');
  signal ram_lhs_lower_i : std_logic_vector(CISE_WIDTH-1 downto 0) := (others => '0');
  signal ram_lhs_upper_o : std_logic_vector(CISE_WIDTH-1 downto 0) := (others => '0');
  signal ram_lhs_lower_o : std_logic_vector(CISE_WIDTH-1 downto 0) := (others => '0');
  
  constant zeros : std_logic_vector(CISE_WIDTH-1 downto 0) := (others => '0');
  
begin
--Port map section
  LHSData <= ram_lhs_o;
  Valid <= ram_valid_o;

--Process section
  SYNC_PROC: process(
							FSL_Clk,
							fsm_rd_state_i, 
							nr_of_reads_i,
							ram_valid_i,
							ram_lhs_upper_i, ram_lhs_lower_i
							)
  begin
	 Clocking :
    if (FSL_Clk'event and FSL_Clk = '1') then
      Resetting :
		if (FSL_Rst = '1') then
        fsm_rd_state_o <= Read_LHS_Upper;
        -- reset for signals
        --output_o <= '0';
        -- Internal Variables
        nr_of_reads_o <= 0;
        --  Internal Registers
		  ram_valid_o <= '0';
        ram_lhs_o <= (others => '0');
        ram_lhs_upper_o <= (others => '0');
        ram_lhs_lower_o <= (others => '0');
      else
        fsm_rd_state_o <= fsm_rd_state_i;
        -- update signals
        --output_o <= output_i;
        -- Internal Variables
        nr_of_reads_o <= nr_of_reads_i;
        --  Internal Registers
		  ram_valid_o <= ram_valid_i;
        ram_lhs_o <= ram_lhs_i;
        ram_lhs_upper_o <= ram_lhs_upper_i;
        ram_lhs_lower_o <= ram_lhs_lower_i;
      end if Resetting;        
    end if Clocking;
  end process;
  
--MOORE State-Machine - Outputs based on state only
  Read_uB : 
  process (fsm_rd_state_o, 
           FSL_S_Exists, FSL_S_Control, FSL_S_Data,  
           nr_of_reads_o,
			  ram_valid_o,
			  ram_lhs_o,
           ram_lhs_upper_o, ram_lhs_lower_o)
  begin
    --fsm_rd_state_i <= fsm_rd_state_o;--default is to stay in current state
    case (fsm_rd_state_o) is
      
      --Streaming has begun... take two 32bit words to later make 64 bit word
      when Read_LHS_Upper =>
        --TRANSISTIONS
        if (FSL_S_Exists = '1' and 
			  (FSL_S_Control = '1' or FSL_S_Control = '0') ) then
          fsm_rd_state_i <= Read_LHS_Lower;
          nr_of_reads_i <= NUMBER_OF_INPUT_WORDS - 1;			 
			 FSL_S_Read <= '1';
          ram_lhs_upper_i <= FSL_S_Data;
			 ram_lhs_i <= FSL_S_Data & zeros;
        else
          fsm_rd_state_i <= Read_LHS_Upper;
			 nr_of_reads_i <= nr_of_reads_o;
          FSL_S_Read <= '0';
          ram_lhs_upper_i <= (others => '0');
			 ram_lhs_i <=(others => '0');
        end if;

        --OUTPUTS
        --  Variables
        --nr_of_reads_i <= nr_of_reads_o; in branch, set state in Read_LHS_Upper
        --  Output Ports
        --FSL_S_Read; in branch
        --  Internal Registers
        ram_valid_i <= '0';
        --ram_lhs_upper_i; in branch, set state in Read_LHS_Upper
        ram_lhs_lower_i <= (others => '0');

      when Read_LHS_Lower =>
        --TRANSISTIONS
        if (FSL_S_Exists = '1' and 
			  (FSL_S_Control = '1' or FSL_S_Control = '0') ) then
          fsm_rd_state_i <= Read_LHS_Upper;
          nr_of_reads_i <= nr_of_reads_o - 1; --made successful read, now decrement
          FSL_S_Read <= '1';
			 ram_valid_i <= not(ram_valid_o);
          ram_lhs_lower_i <= FSL_S_Data;
			 ram_lhs_i <= ram_lhs_upper_o & FSL_S_Data;
        else
			 ram_valid_i <= ram_valid_o;
          fsm_rd_state_i <= Read_LHS_Lower;
          nr_of_reads_i <= nr_of_reads_o;
          FSL_S_Read <= '0';
			 ram_valid_i <= ram_valid_o;
          ram_lhs_lower_i <= (others => '0');
			 ram_lhs_i <= ram_lhs_lower_o & zeros;
        end if;
        
        --OUTPUTS
        --Variables
        --nr_of_reads, keep variable
        --Output Ports
        --FSL_S_Read, in branch
        --Internal Registers
		  --ram_valid_i <= ram_valid_o;, in branch set value in (state := Read_LHS_Lower)
        --ram_lhs_i <= ram_lhs_o;, in branch set value in (state := Read_LHS_Lower)
        ram_lhs_upper_i <= ram_lhs_upper_o; --set value in (state := Read_LHS_Upper)
        --ram_lhs_lower_i, in branch, set value in (state := Read_LHS_Lower)

      when others =>
        --TRANSISTIONS
        fsm_rd_state_i <= Read_LHS_Upper;
        --OUTPUTS
        --  Variables
        nr_of_reads_i <= 0;
        --  Output Ports
        FSL_S_Read <= '0';
        --  Internal Registers
        ram_valid_i <= '0';
        ram_lhs_i <= (others => '0');
        ram_lhs_upper_i <= (others => '0');
        ram_lhs_lower_i <= (others => '0');
    end case;
  end process Read_uB;
  
end architecture CISE;
