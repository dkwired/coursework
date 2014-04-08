
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


entity CAM_Cell is
    Port ( clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           we : in  STD_LOGIC;
           cell_search_bit : in  STD_LOGIC;
           cell_dont_care_bit : in  STD_LOGIC;
			  cell_match_bit_in : in  STD_LOGIC ;
           cell_match_bit_out : out  STD_LOGIC);
end CAM_Cell;

architecture Binary_CAM_Cell of CAM_Cell is

signal sb_sig : std_logic := '0';

begin

    process (clk, we, rst, cell_search_bit)
	 begin
	     if(clk'event and clk='1') then
		      if (rst = '1') then
				    sb_sig <= '0';
		  else
		      if(we = '1') then
				    sb_sig <= cell_search_bit;
			   end if;
			end if;
		 end if;
	 end process;

    process (cell_match_bit_in, cell_search_bit, sb_sig)
    begin
		  cell_match_bit_out <= cell_match_bit_in and not(sb_sig xor cell_search_bit);
    end process;

end Binary_CAM_Cell;