
--
-- Implement the Densely Packed Decimals conversion table
--
-- ---------- ---------- --------- ----------- ---------- ----------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity dpd_to_bcd is
	port(
		b	: in std_logic_vector(9 downto 0);
		d0	: out std_logic_vector(3 downto 0);
		d1	: out std_logic_vector(3 downto 0);
		d2	: out std_logic_vector(3 downto 0)
	);
end dpd_to_bcd;

architecture Behavioral of dpd_to_bcd is

	-- Add User's Signals Here
begin
	
	-- Add User's Logic Here
	process(b)
	begin
		if b(3) = '0' then
			d0 <= ('0' & b(2 downto 0));
			d1 <= ('0' & b(6 downto 4));
			d2 <= ('0' & b(9 downto 7));
		elsif b(2 downto 1) = "00" then
			d0 <= ("100" & b(0));
			d1 <= ('0' & b(6 downto 4));
			d2 <= ('0' & b(9 downto 7));
		elsif b(2 downto 1) = "01" then
			d0 <= ('0' & b(6) & b(5) & b(0));
			d1 <= ("100" & b(4));
			d2 <= ('0' & b(9 downto 7));
		elsif b(2 downto 1) = "10" then
			d0 <= ('0' & b(9) & b(8) & b(0));
			d1 <= ('0' & b(6 downto 4));
			d2 <= ("100" & b(7));
		elsif b(6 downto 5) = "10" then
			d0 <= ("100" & b(0));
			d1 <= ("100" & b(4));
			d2 <= ('0' & b(9 downto 7));
		elsif b(6 downto 5) = "01" then
			d0 <= ("100" & b(0));
			d1 <= ('0' & b(9) & b(8) & b(4));
			d2 <= ("100" & b(7));
		elsif b(6 downto 5) = "00" then
			d0 <= ('0' & b(9) & b(8) & b(0));
			d1 <= ("100" & b(4));
			d2 <= ("100" & b(7));
		else
			d0 <= ("100" & b(0));
			d1 <= ("100" & b(4));
			d2 <= ("100" & b(7));
		end if;
	end process;
			
	
end Behavioral;

