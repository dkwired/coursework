library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity my_Cache is
		Generic( NUMBITS : integer := 32 );
		Port( clk : in  std_logic;
				rst : in  std_logic;
				address : in std_logic_vector( NUMBITS-1 downto 0 );
				valid_in : in std_logic;
				valid_out : out std_logic;
				ack : out std_logic;
				hit : out std_logic );
end my_Cache;

architecture Behavioral of my_Cache is

component Decoder is
	Generic( NUMBITS : integer := 32 );
    Port ( clk : in std_logic;
				rst : in std_logic;
				read_in : in std_logic;
				input : in std_logic_vector( 4 downto 0 );
				output : out std_logic_vector( NUMBITS-1 downto 0 ) );
end component;

component Control_Unit is
	Generic( NUMBITS : integer := 32 );
    Port ( clk : in  std_logic;
				rst : in  std_logic;
				address : in std_logic_vector( NUMBITS-1 downto 0 );
				ack : out std_logic;
				hit : out std_logic;
				match_i : in std_logic_vector(NUMBITS-1 downto 0);
				decoder_i : in std_logic_vector(NUMBITS-1 downto 0);
				read_en : out std_logic;
				valid_in : in std_logic;
				valid_out : in std_logic;
				valid_we : out std_logic );
end component;

component CAM_Array is
	Generic (CAM_WIDTH : integer := 32 ;
				CAM_DEPTH : integer := 32 ) ;
	Port (  clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
			  we_decoded_row_address : in STD_LOGIC_VECTOR(CAM_DEPTH-1 downto 0) ;
           search_word : in  STD_LOGIC_VECTOR (CAM_WIDTH-1 downto 0);
           decoded_match_address : out  STD_LOGIC_VECTOR (CAM_DEPTH-1 downto 0));
end component;

begin

	decode : Decoder
				port map (
				  clk => clk,
				  rst => rst,
				  read_in => read_en,
				  input => address( 11 downto 7 ),
				  output => output
				);

	C_Unit : Control_Unit
				port map (
					clk => clk,
					rst => rst,
					address => address,
					ack => ack,
					hit => hit,
					match_i => match_i,
					decoder_i => decoder_i,
					read_en => read_en,
					valid_in => valid_in,
					valid_out => valid_out,
					valid_we => valid_we
				);
				
	CAM : CAM_Array
				port map (
					clk => clk,
					rst => rst,
					we_decoded_row_address => we_decoded_row_address,
					search_word => address(NUMBITS-1 downto 12),
					decoded_match_address => decoded_match_address
				);
		
	process( decoded_match_address, output, valid_out )
		begin
			if( (decoded_match_addres = output) and valid_out = '1') then
				hit <= '1';
			else
				hit <= '0';
			end if;
	end process;
	
end Behavioral;

