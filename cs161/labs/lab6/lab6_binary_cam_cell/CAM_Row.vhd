

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


entity CAM_Row is
		Generic (CAM_WIDTH : integer := 8) ;
		Port ( clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           we : in  STD_LOGIC;
           search_word : in  STD_LOGIC_VECTOR (CAM_WIDTH-1 downto 0);
           dont_care_mask : in  STD_LOGIC_VECTOR (CAM_WIDTH-1 downto 0);
           row_match : out  STD_LOGIC);
end CAM_Row;

architecture Binary_CAM_Row of CAM_Row is


component CAM_Cell is
    Port ( clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           we : in  STD_LOGIC;
           cell_search_bit : in  STD_LOGIC;
           cell_dont_care_bit : in  STD_LOGIC;
			  cell_match_bit_in : in  STD_LOGIC ;
           cell_match_bit_out : out  STD_LOGIC);
end component ;

for all : CAM_Cell use entity work.CAM_Cell(Binary_CAM_Cell) ; 

signal row_match_sig : std_logic_vector (CAM_WIDTH-1 downto 0);

begin

	  start : CAM_Cell
				port map (
					  clk => clk,
					  rst => rst,
					  we => we,
					  cell_search_bit => search_word(0),
					  cell_match_bit_in => '1',
					  cell_match_bit_out => row_match_sig(0),
					  cell_dont_care_bit => dont_care_mask(0)
					  );

     gen_row : for N in 1 to CAM_WIDTH-1 generate
			gen_row : CAM_Cell
				port map (
					  clk => clk,
					  rst => rst,
					  we => we,
					  cell_search_bit => search_word(N),
					  cell_match_bit_in => row_match_sig(N-1),
					  cell_match_bit_out => row_match_sig(N),
					  cell_dont_care_bit => dont_care_mask(N)
					);
		end generate gen_row;

row_match <= row_match_sig(CAM_WIDTH-1);

end Binary_CAM_Row;









