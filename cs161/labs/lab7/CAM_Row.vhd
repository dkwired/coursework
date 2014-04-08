library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity CAM_Row is
		Generic (CAM_WIDTH : integer := 32) ;
		Port ( clk : in  STD_LOGIC;
				 rst : in  STD_LOGIC;
				 we : in  STD_LOGIC;
				 search_word : in  STD_LOGIC_VECTOR (CAM_WIDTH-1 downto 0);
				 row_match : out  STD_LOGIC;
				-- valid_in : in std_logic;
				 valid_out : out std_logic
			  );
end CAM_Row;

architecture Binary_CAM_Row of CAM_Row is

component CAM_Cell is
    Port ( clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           we : in  STD_LOGIC;
           cell_search_bit : in  STD_LOGIC;
			  cell_match_bit_in : in  STD_LOGIC ;
           cell_match_bit_out : out  STD_LOGIC);
end component ;

for all : CAM_Cell use entity work.CAM_Cell(Binary_CAM_Cell) ; 

signal row_match_sig : std_logic_vector (CAM_WIDTH downto 0) := (others => '0');

begin

	row_match_sig(CAM_WIDTH) <= '1';
	
	gen_row : for N in CAM_WIDTH-1 downto 0 generate
		CAMBit : CAM_Cell
			port map (
				  clk,
				  rst,
				  we,
				  search_word(N),
				  row_match_sig(N+1),
				  row_match_sig(N)
				);
	end generate gen_row;

	row_match <= row_match_sig(0);

end Binary_CAM_Row;









