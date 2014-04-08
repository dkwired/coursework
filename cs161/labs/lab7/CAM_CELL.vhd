
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


entity CAM_Cell is
    Port ( clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           we : in  STD_LOGIC;
           cell_search_bit : in  STD_LOGIC;
			  cell_match_bit_in : in  STD_LOGIC ;
           cell_match_bit_out : out  STD_LOGIC);
end CAM_Cell;

architecture Binary_CAM_Cell of CAM_Cell is

signal sb_sig : std_logic := '0';

begin

    process( clk, rst, we, cell_search_bit, cell_match_bit_in, sb_sig )
	 begin
	     if (rst = '1') then
			   sb_sig <= '0';
		  elsif( clk = '1' and clk'event and we = '1') then
				sb_sig <= cell_search_bit;
		 end if;
	 end process;

    cell_match_bit_out <= cell_match_bit_in and (sb_sig xnor cell_search_bit);

end Binary_CAM_Cell;