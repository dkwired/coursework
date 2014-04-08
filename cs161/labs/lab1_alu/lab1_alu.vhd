--Names: Wojciech Karas, David Klein
--Email: wkara001@ucr.edu, dklei003@ucr.edu
--Lab Section: 022
--Assignment: Lab 1 ALU

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity my_ALU is
	generic( NUMBITS	: natural	:= 4 );
	port(
		A			: in  std_logic_vector(NUMBITS-1 downto 0);
		B			: in  std_logic_vector(NUMBITS-1 downto 0);
		opcode	: in  std_logic_vector(2 downto 0);
		result	: out std_logic_vector(NUMBITS-1 downto 0);
		carryout	: out std_logic;
		overflow	: out std_logic;
		zero		: out std_logic
	);
end my_ALU;

architecture Behavioral of my_alu is

signal A_sig 			: std_logic_vector(NUMBITS downto 0);
signal B_sig 			: std_logic_vector(NUMBITS downto 0);
signal result_sig 	: std_logic_vector(NUMBITS downto 0);
signal carryout_sig  : std_logic;
signal overflow_sig  : std_logic;
signal zero_sig 		: std_logic;

begin

	ALU : process(A, B, opcode)
	
	variable result_var	: std_logic_vector(NUMBITS downto 0);
	
	begin

	--unsigned add
	if(opcode = "000") then
	
	result_sig <= ('0' & A) + ('0' & B);
	result_var := ('0' & A) + ('0' & B);
	
	UNSIGADD_OVERFLOW : if(result_var(NUMBITS) = '1') then
		overflow_sig <= '1';
	else
		overflow_sig <= '0';
	end if UNSIGADD_OVERFLOW;
	
	--signed add
	elsif(opcode = "001") then
	
	result_sig <= (A(NUMBITS-1) & A) + (B(NUMBITS-1) & B);
	result_var := (A(NUMBITS-1) & A) + (B(NUMBITS-1) & B);
	
	SIGADD_OVERFLOW : if(A (NUMBITS-1) = '0' AND B(NUMBITS-1) = '0' AND result_var(NUMBITS-1) = '1') then
		overflow_sig <= '1';
	elsif (A(NUMBITS-1) = '1' AND B(NUMBITS-1) = '1' AND result_var(NUMBITS-1) = '0') then
		overflow_sig <= '1';
	else
		overflow_sig <= '0';		
	end if SIGADD_OVERFLOW;

	--unsigned sub
	elsif(opcode = "010") then
	
	result_sig <= ('0' & A) - ('0' & B);
	result_var := ('0' & A) - ('0' & B);
	
	UNSIGSUB_OVERFLOW : if( A < B ) then
		overflow_sig <= '1';
		result_sig <= '0' & result_var(NUMBITS-1 downto 0);
	else
		overflow_sig <= '0';
	end if UNSIGSUB_OVERFLOW;

	--signed sub
	elsif(opcode = "011") then
	
	result_sig <= (A(NUMBITS-1) & A) - (B(NUMBITS-1) & B);
	result_var := (A(NUMBITS-1) & A) - (B(NUMBITS-1) & B);
	
	SIGSUB_OVERFLOW : if(A(NUMBITS-1) = '0' AND B(NUMBITS-1) = '0' AND result_var(NUMBITS-1) = '1') then
		overflow_sig <= '1';
	elsif (A(NUMBITS-1) = '1' AND B(NUMBITS-1) = '0' AND result_var(NUMBITS-1) = '0') then
		overflow_sig <= '1';
	else
		overflow_sig <= '0';
	end if SIGSUB_OVERFLOW;
	
	--bit-wise AND
	elsif(opcode = "100") then
	
	result_sig <= ('0' & A) AND ('0' & B);
	result_var := ('0' & A) AND ('0' & B);
	
	--bit-wise OR
	elsif(opcode = "101") then
	
	result_sig <= ('0' & A) OR ('0' & B);
	result_var := ('0' & A) OR ('0' & B);
	
	--bit-wise XOR
	elsif(opcode = "110") then
	
	result_sig <= ('0' & A) XOR ('0' & B);
	result_var := ('0' & A) XOR ('0' & B);
	
	--divide A by 2
	elsif(opcode = "111") then	
	
	result_sig <= "00" & A(NUMBITS-1 downto 1);
	result_var := "00" & A(NUMBITS-1 downto 1);
	
	end if START_ALU;
	
	ZERO_CHECK : if( result_var = 0 ) then
		zero_sig <= '1';
	else
		zero_sig <= '0';
	end if ZERO_CHECK;
	
	end process ALU;
	
	result <= result_sig(NUMBITS-1 downto 0);
	overflow <= overflow_sig;
	carryout <= result_sig(NUMBITS);
	zero <= zero_sig;
	
end Behavioral;