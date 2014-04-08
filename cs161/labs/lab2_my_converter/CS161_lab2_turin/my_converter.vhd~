----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    08:02:53 04/24/2012 
-- Design Name: 
-- Module Name:    my_converter - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use ieee.numeric_bit.all;


-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity my_converter is
	generic(
		numbits	: integer	:= 32
	);
    Port ( floating : in  STD_LOGIC_VECTOR(numbits - 1 downto 0);
           fixed : out  STD_LOGIC_VECTOR(numbits - 1 downto 0));
end my_converter;

architecture Behavioral of my_converter is
	signal sign_sig: std_logic;
	signal exponent: std_logic_vector(7 downto 0);
	signal mantissa: std_logic_vector(22 downto 0);
	
	signal fixed_sig: std_logic_vector(31 downto 0);
	signal signal_to_shift: std_logic_vector(38 downto 0);
	signal pos_signal_to_shift_1: std_logic_vector(38 downto 0);
	signal pos_signal_to_shift_2: std_logic_vector(38 downto 0);
	signal pos_signal_to_shift_3: std_logic_vector(38 downto 0);
	signal pos_signal_to_shift_4: std_logic_vector(38 downto 0);
	signal pos_signal_to_shift_5: std_logic_vector(38 downto 0);
	signal neg_signal_to_shift_1: std_logic_vector(38 downto 0);
	signal neg_signal_to_shift_2: std_logic_vector(38 downto 0);
	signal neg_signal_to_shift_3: std_logic_vector(38 downto 0);
	signal neg_signal_to_shift_4: std_logic_vector(38 downto 0);
	signal neg_signal_to_shift_5: std_logic_vector(38 downto 0);
	signal pos_shift_sig: std_logic_vector(38 downto 0);
	signal neg_shift_sig: std_logic_vector(38 downto 0);
	signal shift_enable: std_logic_vector(7 downto 0);
	signal mux_select: std_logic;
	signal positive_shift_out: std_logic;
	signal negative_shift_out: std_logic;


begin
	my_converter_process: process( floating, sign_sig, exponent, mantissa )
		begin
			exponent <= floating(30 downto 23);
			mantissa <= floating(22 downto 0);
			sign_sig <= floating(31);		
		end process my_converter_process;
		
	controller: process( exponent, mantissa, signal_to_shift, shift_enable, mux_select , positive_shift_out, negative_shift_out )
		begin
			signal_to_shift <= "000000000000000" & '1' & mantissa(22 downto 0);
			if( exponent > 127 ) then
				shift_enable <= exponent - 127;
				mux_select <= '0';
			else
				shift_enable <= 127 - exponent;
				mux_select <= '1';			
			end if;
			
			--Positive Shift
			POS_SHIFT: if( shift_enable > 39 ) then
				positive_shift_out <= '0';-- junk <= (others => '0');
				
			else
				--perform positive shift
				positive_shift_out <= '1';
			end if POS_SHIFT;
			
			--Negative Shift
			NEGATIVE_SHIFT:if( shift_enable > 24 ) then
				negative_shift_out <= '0';
			else
				--perform negative shift
				negative_shift_out <= '1';
			end if NEGATIVE_SHIFT;
		end process controller;
		
	--SHIFT 1 BLOCK - POS
	shift_1_postive: process( signal_to_shift, shift_enable, positive_shift_out )
		begin
			if(shift_enable(0) = '1' AND positive_shift_out = '1') then
				pos_signal_to_shift_1 <= signal_to_shift(37 downto 0) & '0';
			else
				pos_signal_to_shift_1 <= signal_to_shift;
			end if;
		end process shift_1_postive;
	
	--SHIFT 2 BLOCK - POS (LEFT)
	shift_2_postive: process( shift_enable, positive_shift_out, pos_signal_to_shift_1 )
		begin
			if(shift_enable(1) = '1' AND positive_shift_out = '1') then
				pos_signal_to_shift_2 <= pos_signal_to_shift_1(36 downto 0) & "00";
			else
				pos_signal_to_shift_2 <= pos_signal_to_shift_1;
			end if;
		end process shift_2_postive;
		
	--SHIFT 4 BLOCK - POS (LEFT)
	shift_4_postive: process( shift_enable, positive_shift_out, pos_signal_to_shift_2	)
		begin
			if(shift_enable(2) = '1' AND positive_shift_out = '1') then
				pos_signal_to_shift_3 <= pos_signal_to_shift_2(34 downto 0) & x"0";
			else
				pos_signal_to_shift_3 <= pos_signal_to_shift_2;
			end if;
		end process shift_4_postive;
		
	--SHIFT 8 BLOCK - POS (LEFT)
	shift_8_postive: process( shift_enable, positive_shift_out, pos_signal_to_shift_3 )
		begin
			if(shift_enable(3) = '1' AND positive_shift_out = '1') then
				pos_signal_to_shift_4 <= pos_signal_to_shift_3(30 downto 0) & x"00";
			else
				pos_signal_to_shift_4 <= pos_signal_to_shift_3;
			end if;
		end process shift_8_postive;
		
	--SHIFT 16 BLOCK - POS (LEFT)
	shift_16_postive: process( shift_enable, positive_shift_out, pos_signal_to_shift_4 )
		begin
			if(shift_enable(4) = '1' AND positive_shift_out = '1') then
				pos_signal_to_shift_5 <= pos_signal_to_shift_4(22 downto 0) & x"0000";
			else
				pos_signal_to_shift_5 <= pos_signal_to_shift_4;
			end if;
		end process shift_16_postive;
		
	--SHIFT 1 BLOCK - NEG (RIGHT)
	shift_1_negative: process( signal_to_shift, shift_enable, negative_shift_out )
		begin
			if(shift_enable(0) = '1' AND negative_shift_out = '1') then
				neg_signal_to_shift_1 <= '0' & signal_to_shift(38 downto 1);
			else
				neg_signal_to_shift_1 <= signal_to_shift;
			end if;
		end process shift_1_negative;
	
	--SHIFT 2 BLOCK - NEG (RIGHT)
	shift_2_negative: process( shift_enable, negative_shift_out, neg_signal_to_shift_1 )
		begin
			if(shift_enable(1) = '1' AND negative_shift_out = '1') then
				neg_signal_to_shift_2 <= "00" & neg_signal_to_shift_1(38 downto 2);
			else
				neg_signal_to_shift_2 <= neg_signal_to_shift_1;
			end if;
		end process shift_2_negative;
		
	--SHIFT 4 BLOCK - NEG (RIGHT)
	shift_4_negative: process( shift_enable, negative_shift_out, neg_signal_to_shift_2 )
		begin
			if(shift_enable(2) = '1' AND negative_shift_out = '1') then
				neg_signal_to_shift_3 <= x"0" & neg_signal_to_shift_2(38 downto 4);
			else
				neg_signal_to_shift_3 <= neg_signal_to_shift_2;
			end if;
		end process shift_4_negative;
		
	--SHIFT 8 BLOCK - NEG (RIGHT)
	shift_8_negative: process( shift_enable, negative_shift_out, neg_signal_to_shift_3 )
		begin
			if(shift_enable(3) = '1' AND negative_shift_out = '1') then
				neg_signal_to_shift_4 <= x"00" & neg_signal_to_shift_3(38 downto 8);
			else
				neg_signal_to_shift_4 <= neg_signal_to_shift_3;
			end if;
		end process shift_8_negative;
		
	--SHIFT 16 BLOCK - NEG (RIGHT)
	shift_16_negative: process( shift_enable, negative_shift_out, neg_signal_to_shift_4 )
		begin
			if(shift_enable(4) = '1' AND negative_shift_out = '1') then
				neg_signal_to_shift_5 <= x"0000" & neg_signal_to_shift_4(38 downto 16);
			else
				neg_signal_to_shift_5 <= neg_signal_to_shift_4;
			end if;
		end process shift_16_negative;
		
	sign_select_process: process( sign_sig, pos_shift_sig, neg_shift_sig, pos_signal_to_shift_5, neg_signal_to_shift_5 )
		begin
			if( sign_sig = '1' ) then
				neg_shift_sig <= (not neg_signal_to_shift_5) + 1;
				pos_shift_sig <= pos_signal_to_shift_5;
			else
				neg_shift_sig <= neg_signal_to_shift_5;
				pos_shift_sig <= pos_signal_to_shift_5;
			end if;
		end process sign_select_process;
		
	--MUX - controls whether to output the positive or negative signal
	shift_select_mux: process( mux_select, pos_shift_sig, neg_shift_sig )
		begin
			if( mux_select = '0' ) then
				fixed_sig <= neg_shift_sig(31 downto 0);
			else
				fixed_sig <= pos_shift_sig(38 downto 7);
			end if;
		end process shift_select_mux;
		
	fixed <= fixed_sig;
		
end Behavioral;

