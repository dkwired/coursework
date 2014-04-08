library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity CAM_Array is
	Generic (CAM_WIDTH : integer := 32 ;
				CAM_DEPTH : integer := 32 ) ;
	Port (  clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
			  we_decoded_row_address : in STD_LOGIC_VECTOR(CAM_DEPTH-1 downto 0) ;
           search_word : in  STD_LOGIC_VECTOR (CAM_WIDTH-1 downto 0);
           decoded_match_address : out  STD_LOGIC_VECTOR (CAM_DEPTH-1 downto 0)
		  );
end CAM_Array;

architecture Binary_Array of CAM_Array is

component CAM_Row is
	Generic (CAM_WIDTH : integer := 32);
	Port (  clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           we : in  STD_LOGIC;
           search_word : in  STD_LOGIC_VECTOR (CAM_WIDTH-1 downto 0);
           row_match : out  STD_LOGIC
			);
end component ;

for all : CAM_Row use entity work.CAM_Row(Binary_CAM_Row);

begin

     gen_arr : for N in CAM_DEPTH-1 downto 0 generate
			CAMWord : CAM_Row
			Generic Map (CAM_WIDTH => CAM_WIDTH)
				port map (
					  clk,
					  rst,
					  we_decoded_row_address(N),
					  search_word,
					  decoded_match_address(N)
					);
		end generate gen_arr;

end Binary_Array;

