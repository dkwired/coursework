library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Control_Unit is
		Generic( NUMBITS : integer := 32 );
		Port( clk : in  std_logic;
				rst : in  std_logic;
				address : in std_logic_vector( NUMBITS-1 downto 0 );
				ack : out std_logic;
				hit : out std_logic;
				match_i : in std_logic_vector(NUMBITS-1 downto 0);
				decoder_i : in std_logic_vector(NUMBITS-1 downto 0);
				read_en : out std_logic;
				valid_in : in std_logic;
				valid_out : in std_logic;
				valid_mem : out std_logic;
				valid_we : out std_logic );

end Control_Unit;

architecture Behavioral of Control_Unit is

--States for state machine in enumerated form
type FSM_RD_STATE_TYPE is (WAIT_FOR_VALID, MATCH, 
                           UPDATE);
signal fsm_rd_state_i, fsm_rd_state_o : FSM_RD_STATE_TYPE;
signal address_o : std_logic_vector(NUMBITS-1 downto 0);
signal address_i : std_logic_vector(NUMBITS-1 downto 0);
signal hit_i : std_logic;
signal hit_o : std_logic;

begin

	SYNC_PROC: process( clk, rst, fsm_rd_state_i, hit_out_sig )
		begin
		
			-- clock and reset
			Clocking : if (clk'event and clk = '1') then
				Resetting : if (rst = '1') then
					fsm_rd_state_o <= WAIT_FOR_VALID;
					hit_o <= '0';
					address_o <= (others => '0');
				else
					hit_o <= hit_i;
					fsm_rd_state_o <= fsm_rd_state_i;
					address_o <= address_i;
				end if Resetting;
			end if Clocking;
	end process;
	
	FSM : process( fsm_rd_state_o, valid_in, hit_in_sig, address_o, address_i )
		begin
			
			case (fsm_rd_state_o) is
				when WAIT_FOR_VALID =>
					if( valid_in = '1' ) then
						fsm_rd_state_i <= MATCH;
						ack <= '1';
						address_i <= address;
						read_en <= '1';
						hit_i <= hit_o;
					else
						fsm_rd_state_i <= WAIT_FOR_VALID;
						ack <= '0';
						hit_i <= hit_o;
						address_i <= address_o;
					end if;
					
				when MATCH =>
					if( decoder_i = match_i ) then
						fsm_rd_state_i <= WAIT_FOR_VALID;
						hit_i <= '1';
						
					else
						fsm_rd_state_i <= UPDATE;
						hit_i <= '0';
						
					end if;
				
				when UPDATE =>
					fsm_rd_state_i <= WAIT_FOR_VALID;
					valid_mem <= '1';
					address_i <= address_o;
			end case;
	
	end process;

end Behavioral;

