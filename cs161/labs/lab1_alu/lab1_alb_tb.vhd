--Names: Wojciech Karas, David Klein
--Email: wkara001@ucr.edu, dklei003@ucr.edu
--Lab Section: 022
--Assignment: Lab 1 ALU Testbench

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.all;
USE ieee.numeric_std.ALL;
USE ieee.std_logic_arith.all;
 
ENTITY my_ALU_tb IS
END my_ALU_tb;
 
ARCHITECTURE behavior OF my_ALU_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT my_alu
	 generic(
		numbits	: natural	:= 4
	 );
    PORT(
         A : IN  std_logic_vector(0 to 3);
         B : IN  std_logic_vector(0 to 3);
         opcode : IN  std_logic_vector(0 to 2);
         result : OUT  std_logic_vector(0 to 3);
         carryout : OUT  std_logic;
         overflow : OUT  std_logic;
         zero : OUT  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal A : std_logic_vector(0 to 3) := (others => '0');
   signal B : std_logic_vector(0 to 3) := (others => '0');
   signal opcode : std_logic_vector(0 to 2) := (others => '0');

 	--Outputs
   signal result : std_logic_vector(0 to 3);
   signal carryout : std_logic;
   signal overflow : std_logic;
   signal zero : std_logic;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: my_alu generic map(
		numbits => 4
	)
	PORT MAP (
          A => A,
          B => B,
          opcode => opcode,
          result => result,
          carryout => carryout,
          overflow => overflow,
          zero => zero
        );


   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100ms.
		wait for 10 ns;
		
		-- --------------------------------------------------------------------------------
		-- --------------------------------------------------------------------------------
		-- Testing Unsigned Add
		-- --------------------------------------------------------------------------------
		-- --------------------------------------------------------------------------------
		report "Testing Unsigned Add";
		opcode <= "000";
		
			-- Test 1 zero
			A <= conv_std_logic_vector(0, 4);
			B <= conv_std_logic_vector(0, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(0, 4) 	report "Test_1: result incorrect" 	severity Warning;
			assert carryout = '0' 								report "Test_1: carryout incorrect"	severity Warning;
			assert overflow = '0' 								report "Test_1: overflow incorrect"	severity Warning;
			assert zero = '1'										report "Test_1: zero incorrect"		severity Warning;
			
			--Enter Additional Test Cases here!
			-- Test 2	sum +X
			A <= conv_std_logic_vector(1, 4);
			B <= conv_std_logic_vector(2, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(3, 4) 	report "Test_2: result incorrect" 	severity Warning;
			assert carryout = '0' 								report "Test_2: carryout incorrect"	severity Warning;
			assert overflow = '0' 								report "Test_2: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_2: zero incorrect"		severity Warning;
			
			-- Test 3 sum min+1
			A <= conv_std_logic_vector(0, 4);
			B <= conv_std_logic_vector(1, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(1, 4) 	report "Test_3: result incorrect" 	severity Warning;
			assert carryout = '0' 								report "Test_3: carryout incorrect"	severity Warning;
			assert overflow = '0' 								report "Test_3: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_3: zero incorrect"		severity Warning;
			
			-- Test 4 sum max-1
			A <= conv_std_logic_vector(7, 4);
			B <= conv_std_logic_vector(7, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(14, 4) 	report "Test_4: result incorrect" 	severity Warning;
			assert carryout = '0' 								report "Test_4: carryout incorrect"	severity Warning;
			assert overflow = '0' 								report "Test_4: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_4: zero incorrect"		severity Warning;
			
			-- Test 5 sum max
			A <= conv_std_logic_vector(8, 4);
			B <= conv_std_logic_vector(7, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(15, 4) 	report "Test_5: result incorrect" 	severity Warning;
			assert carryout = '0' 								report "Test_5: carryout incorrect"	severity Warning;
			assert overflow = '0' 								report "Test_5: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_5: zero incorrect"		severity Warning;
			
			-- Test 6 overflow
			A <= conv_std_logic_vector(8, 4);
			B <= conv_std_logic_vector(9, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(1, 4) 	report "Test_6: result incorrect" 	severity Warning;
			assert carryout = '1' 								report "Test_6: carryout incorrect"	severity Warning;
			assert overflow = '1' 								report "Test_6: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_6: zero incorrect"		severity Warning;
		-- --------------------------------------------------------------------------------
		-- --------------------------------------------------------------------------------
		-- Testing Signed add
		-- --------------------------------------------------------------------------------
		-- --------------------------------------------------------------------------------
		opcode <= "001";
		report "Testing Signed Add";
			-- Test 1 zero
			A <= conv_std_logic_vector(0, 4);
			B <= conv_std_logic_vector(0, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(0, 4) 	report "Test_1: result incorrect" 	severity Warning;
			assert carryout = '0' 								report "Test_1: carryout incorrect"	severity Warning;
			assert overflow = '0' 								report "Test_1: overflow incorrect"	severity Warning;
			assert zero = '1'										report "Test_1: zero incorrect"		severity Warning;
			
			--Enter Additional Test Cases here!
			-- Test 2	sum +X
			A <= conv_std_logic_vector(2, 4);
			B <= conv_std_logic_vector(-1, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(1, 4) 	report "Test_2: result incorrect" 	severity Warning;
			assert carryout = '0' 								report "Test_2: carryout incorrect"	severity Warning;
			assert overflow = '0' 								report "Test_2: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_2: zero incorrect"		severity Warning;
			
			-- Test 3 sum min+1
			A <= conv_std_logic_vector(-4, 4);
			B <= conv_std_logic_vector(-3, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(-7, 4) 	report "Test_3: result incorrect" 	severity Warning;
			assert carryout = '1' 								report "Test_3: carryout incorrect"	severity Warning;
			assert overflow = '0' 								report "Test_3: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_3: zero incorrect"		severity Warning;
			
			-- Test 4 sum max-1
			A <= conv_std_logic_vector(3, 4);
			B <= conv_std_logic_vector(3, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(6, 4) 	report "Test_4: result incorrect" 	severity Warning;
			assert carryout = '0' 								report "Test_4: carryout incorrect"	severity Warning;
			assert overflow = '0' 								report "Test_4: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_4: zero incorrect"		severity Warning;
			
			-- Test 5 sum max
			A <= conv_std_logic_vector(4, 4);
			B <= conv_std_logic_vector(3, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(7, 4) 	report "Test_5: result incorrect" 	severity Warning;
			assert carryout = '0' 								report "Test_5: carryout incorrect"	severity Warning;
			assert overflow = '0' 								report "Test_5: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_5: zero incorrect"		severity Warning;
			
			-- Test 6 overflow
			A <= conv_std_logic_vector(5, 4);
			B <= conv_std_logic_vector(4, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(9, 4) 	report "Test_6: result incorrect" 	severity Warning;
			assert carryout = '0' 								report "Test_6: carryout incorrect"	severity Warning;
			assert overflow = '1' 								report "Test_6: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_6: zero incorrect"		severity Warning;
			
			--Enter Additional Test Cases here!
			-- Test 7	sum -X
			A <= conv_std_logic_vector(-1, 4);
			B <= conv_std_logic_vector(-2, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(-3, 4) 	report "Test_7: result incorrect" 	severity Warning;
			assert carryout = '1' 								report "Test_7: carryout incorrect"	severity Warning;
			assert overflow = '0' 								report "Test_7: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_7: zero incorrect"		severity Warning;
		-- --------------------------------------------------------------------------------
		-- --------------------------------------------------------------------------------
		-- Testing Unsigned Subtract
		-- --------------------------------------------------------------------------------
		-- --------------------------------------------------------------------------------
		report "Testing Unsigned Subtract";
		opcode <= "010";
		
			-- Test 1
			A <= conv_std_logic_vector(2, 4);
			B <= conv_std_logic_vector(1, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(1, 4) 	report "Test_1: result incorrect" 	severity Warning;
			assert carryout = '0' 								report "Test_1: carryout incorrect"	severity Warning;
			assert overflow = '0' 								report "Test_1: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_1: zero incorrect"		severity Warning;
			
			--Enter Additional Test Cases here!
			-- Test 2	sum +X
			A <= conv_std_logic_vector(6, 4);
			B <= conv_std_logic_vector(4, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(2, 4) 	report "Test_2: result incorrect" 	severity Warning;
			assert carryout = '0' 								report "Test_2: carryout incorrect"	severity Warning;
			assert overflow = '0' 								report "Test_2: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_2: zero incorrect"		severity Warning;
			
			-- Test 3 sum min+1
			A <= conv_std_logic_vector(15, 4);
			B <= conv_std_logic_vector(14, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(1, 4) 	report "Test_3: result incorrect" 	severity Warning;
			assert carryout = '0' 								report "Test_3: carryout incorrect"	severity Warning;
			assert overflow = '0' 								report "Test_3: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_3: zero incorrect"		severity Warning;
			
			-- Test 4 sum max-1
			A <= conv_std_logic_vector(15, 4);
			B <= conv_std_logic_vector(1, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(14, 4) 	report "Test_4: result incorrect" 	severity Warning;
			assert carryout = '0' 								report "Test_4: carryout incorrect"	severity Warning;
			assert overflow = '0' 								report "Test_4: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_4: zero incorrect"		severity Warning;
			
			-- Test 5 sum max
			A <= conv_std_logic_vector(15, 4);
			B <= conv_std_logic_vector(0, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(15, 4) 	report "Test_5: result incorrect" 	severity Warning;
			assert carryout = '0' 								report "Test_5: carryout incorrect"	severity Warning;
			assert overflow = '0' 								report "Test_5: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_5: zero incorrect"		severity Warning;
			
			-- Test 6 overflow
			A <= conv_std_logic_vector(7, 4);
			B <= conv_std_logic_vector(8, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(-1, 4) 	report "Test_6: result incorrect" 	severity Warning;
			assert carryout = '0' 								report "Test_6: carryout incorrect"	severity Warning;
			assert overflow = '1' 								report "Test_6: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_6: zero incorrect"		severity Warning;
		
		-- --------------------------------------------------------------------------------
		-- --------------------------------------------------------------------------------
		-- Testing Signed Subtract
		-- --------------------------------------------------------------------------------
		-- --------------------------------------------------------------------------------
		opcode <= "011";
		report "Testing Signed Subtract";
			-- Test 1
			A <= conv_std_logic_vector(2, 4);
			B <= conv_std_logic_vector(1, 4);

			wait for 10 ns;
			assert result = conv_std_logic_vector(1, 4)	report "Test_1: result incorrect" 	severity Warning;
			assert carryout = '0' 								report "Test_1: carryout incorrect"	severity Warning;
			assert overflow = '0' 								report "Test_1: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_1: zero incorrect"		severity Warning;
			
			--Enter Additional Test Cases here!
			-- Test 2	sum +X
			A <= conv_std_logic_vector(2, 4);
			B <= conv_std_logic_vector(-1, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(3, 4) 	report "Test_2: result incorrect" 	severity Warning;
			assert carryout = '0' 								report "Test_2: carryout incorrect"	severity Warning;
			assert overflow = '0' 								report "Test_2: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_2: zero incorrect"		severity Warning;
			
			-- Test 3 sum min+1
			A <= conv_std_logic_vector(-7, 4);
			B <= conv_std_logic_vector(1, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(-8, 4) 	report "Test_3: result incorrect" 	severity Warning;
			assert carryout = '1' 								report "Test_3: carryout incorrect"	severity Warning;
			assert overflow = '0' 								report "Test_3: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_3: zero incorrect"		severity Warning;
			
			-- Test 4 sum max-1
			A <= conv_std_logic_vector(7, 4);
			B <= conv_std_logic_vector(0, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(7, 4) 	report "Test_4: result incorrect" 	severity Warning;
			assert carryout = '0' 								report "Test_4: carryout incorrect"	severity Warning;
			assert overflow = '0' 								report "Test_4: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_4: zero incorrect"		severity Warning;
			
			-- Test 5 sum max
			A <= conv_std_logic_vector(7, 4);
			B <= conv_std_logic_vector(0, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(7, 4) 	report "Test_5: result incorrect" 	severity Warning;
			assert carryout = '0' 								report "Test_5: carryout incorrect"	severity Warning;
			assert overflow = '0' 								report "Test_5: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_5: zero incorrect"		severity Warning;
			
			-- Test 6 overflow
			A <= conv_std_logic_vector(-5, 4);
			B <= conv_std_logic_vector(-4, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(-1, 4) 	report "Test_6: result incorrect" 	severity Warning;
			assert carryout = '1' 								report "Test_6: carryout incorrect"	severity Warning;
			assert overflow = '0' 								report "Test_6: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_6: zero incorrect"		severity Warning;
			
			--Enter Additional Test Cases here!
			-- Test 7	sum -X
			A <= conv_std_logic_vector(-3, 4);
			B <= conv_std_logic_vector(-1, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(-2, 4) 	report "Test_7: result incorrect" 	severity Warning;
			assert carryout = '0' 								report "Test_7: carryout incorrect"	severity Warning;
			assert overflow = '0' 								report "Test_7: overflow incorrect"	severity Warning;
			assert zero = '0'										report "Test_7: zero incorrect"		severity Warning;
      
		-- --------------------------------------------------------------------------------
		-- --------------------------------------------------------------------------------
		-- Testing And
		-- --------------------------------------------------------------------------------
		-- --------------------------------------------------------------------------------
		opcode <= "100";
		report "Testing And";
			-- Test 1
			A <= "1010";
			B <= "1010";
			
			wait for 10 ns;
			assert result = "0000"	report "Test_1: result incorrect"	severity Warning;
			
			--Enter Additional Test Cases here!
		
		-- --------------------------------------------------------------------------------
		-- --------------------------------------------------------------------------------
		-- Testing OR
		-- --------------------------------------------------------------------------------
		-- --------------------------------------------------------------------------------
		opcode <= "101";
		report "Testing OR";
			-- Test 1
			A <= "1010";
			B <= "1010";
			
			wait for 10 ns;
			assert result = "1111"	report "Test_1: result incorrect"	severity Warning;
			
			--Enter Additional Test Cases here!
			
		-- --------------------------------------------------------------------------------
		-- --------------------------------------------------------------------------------
		-- Testing XOR
		-- --------------------------------------------------------------------------------
		-- --------------------------------------------------------------------------------
		opcode <= "110";
		report "Testing XOR";
			-- Test 1
			A <= "1010";
			B <= "1010";
			
			wait for 10 ns;
			assert result = "1111"	report "Test_1: result incorrect"	severity Warning;
			
			--Enter Additional Test Cases here!
			
			-- --------------------------------------------------------------------------------
		-- --------------------------------------------------------------------------------
		-- Testing Divide by 2
		-- --------------------------------------------------------------------------------
		-- --------------------------------------------------------------------------------
		opcode <= "111";
		report "Testing Divide by 2";
			-- Test 1
			A <= conv_std_logic_vector(2, 4);
			
			wait for 10 ns;
			assert result = conv_std_logic_vector(1, 4)	report "Test_1: result incorrect"	severity Warning;
			
			--Enter Additional Test Cases here!
			
		wait;
   end process;

END;
