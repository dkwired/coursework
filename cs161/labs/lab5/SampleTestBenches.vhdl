






-- TestBench For dpd_to_bcd converter
-- ---------- ---------- --------- ----------- ---------- ----------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
ENTITY dpd_to_bcd_tb IS
END dpd_to_bcd_tb;
 
ARCHITECTURE behavior OF dpd_to_bcd_tb IS 
 
    COMPONENT dpd_to_bcd
    PORT(
         b : IN  std_logic_vector(9 downto 0);
         d0 : OUT  std_logic_vector(3 downto 0);
         d1 : OUT  std_logic_vector(3 downto 0);
         d2 : OUT  std_logic_vector(3 downto 0)
        );
    END COMPONENT;
    
   signal b : std_logic_vector(9 downto 0) := (others => '0');
   signal d0 : std_logic_vector(3 downto 0);
   signal d1 : std_logic_vector(3 downto 0);
   signal d2 : std_logic_vector(3 downto 0);
 
BEGIN
   uut: dpd_to_bcd PORT MAP (
          b => b,
          d0 => d0,
          d1 => d1,
          d2 => d2
        );

   sim_proc: process
   begin		
      
		-- Test Case(s): Three small digits
		b <= "1111100101"; -- (765)
		wait for 10 ns;
		
		-- Test Case(s): Two small digits, one large 
		b <= "1111101000"; -- (768)
		wait for 10 ns;
		b <= "0010111010"; -- (192)
		wait for 10 ns;
		b <= "1010001100"; -- (904)
		wait for 10 ns;
		
		-- Test Case(s): One small digit, two large
		b <= "1010001110"; -- (984)
		wait for 10 ns;
		b <= "1011011110"; -- (598)
		wait for 10 ns;
		b <= "1100101111"; -- (869)
		wait for 10 ns;
		
		-- Test Case(s): Three large digits
		b <= "1111111111"; -- (999)
		wait for 10 ns;
		b <= "0001101110"; -- (888)
		wait for 10 ns;

      wait;
   end process;

END;
