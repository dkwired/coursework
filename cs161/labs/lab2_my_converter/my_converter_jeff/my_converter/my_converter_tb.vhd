--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   16:12:05 04/27/2012
-- Design Name:   
-- Module Name:   C:/Documents and Settings/Embedded Systems Lab/Desktop/my_converter_jeff/my_converter/my_converter_tb.vhd
-- Project Name:  my_converter
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: my_converter
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
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
