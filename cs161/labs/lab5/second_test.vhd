-- TestBench For dpd_adder converter
-- ---------- ---------- --------- ----------- ---------- ----------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
ENTITY dpd_adder_tb IS
END dpd_adder_tb;
 
ARCHITECTURE behavior OF dpd_adder_tb IS 
 
    COMPONENT dpd_adder
    PORT(
         dpd_val_1 : IN  std_logic_vector(9 downto 0);
         dpd_val_2 : IN  std_logic_vector(9 downto 0);
         c_in : IN  std_logic;
         bcd_result : OUT  std_logic_vector(11 downto 0);
         c_out : OUT  std_logic
        );
    END COMPONENT;

   signal dpd_val_1 : std_logic_vector(9 downto 0) := (others => '0');
   signal dpd_val_2 : std_logic_vector(9 downto 0) := (others => '0');
   signal c_in : std_logic := '0';
   signal bcd_result : std_logic_vector(11 downto 0);
   signal c_out : std_logic;
 
BEGIN

   uut: dpd_adder PORT MAP (
          dpd_val_1 => dpd_val_1,
          dpd_val_2 => dpd_val_2,
          c_in => c_in,
          bcd_result => bcd_result,
          c_out => c_out
        );

   sim_proc: process
   begin		
		-- 999 + 001
		dpd_val_1 <= "0011111111";
		dpd_val_2 <= "0000000001";
		c_in <= '0';
		wait for 10 ns;
		
		-- 999 + 000 + (1)
		dpd_val_1 <= "0011111111";
		dpd_val_2 <= "0000000000";
		c_in <= '1';
		wait for 10 ns;
		
		-- 732 + 108
		dpd_val_1 <= "1110110010";
		dpd_val_2 <= "0010001000";
		c_in <= '0';
		wait for 10 ns;
		
		-- 091 + 806
		dpd_val_1 <= "0000011011";
		dpd_val_2 <= "1100001100";
		c_in <= '0';
		wait for 10 ns;
      wait;
   end process;

END;