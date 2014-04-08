----------------------------------------------------------------------------------
--Names: Jeffrey Shaw, David Klien
--Login: shawj, kliend
--Email: shawj@cs.ucr.edu, dklie003@ucr.edu
--Lab Section: 022
--Assignment: Lab #2
--I acknowledge all content is original.
----------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY my_converter_tb IS
END my_converter_tb;
 
ARCHITECTURE behavior OF my_converter_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT my_converter
    PORT(
         floating : IN  std_logic_vector(31 downto 0);
         fixed : OUT  std_logic_vector(31 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal floating : std_logic_vector(31 downto 0) := (others => '0');

 	--Outputs
   signal fixed : std_logic_vector(31 downto 0);
   constant clock_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: my_converter PORT MAP (
          floating => floating,
          fixed => fixed
        );



   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for clock_period;

		-- --------------------------------------------------------------------------------
		-- --------------------------------------------------------------------------------
		-- Testing
		-- --------------------------------------------------------------------------------
		-- --------------------------------------------------------------------------------
		report "Testing";

		floating <= "01000001000001000000000000000000";
		
      wait;
   end process;

END;
