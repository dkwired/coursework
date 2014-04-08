library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity mux_4_1 is
     Port ( 
            A_0 : in std_logic;
            A_1 : in std_logic;
            A_2 : in std_logic;
            A_3 : in std_logic;
            sel : in std_logic_vector( 1 downto 0);
            output : out std_logic );
end mux_4_1;

architecture Behavioral of mux_4_1 is

begin
   process( sel, A_0, A_1, A_2, A_3)
   begin
      case sel is
         when "00" => output <= A_0;
         when "01" => output <= A_1;
         when "10" => output <= A_2;
         when "11" => output <= A_3;
         when others => output <= A_0;
      end case;
   end process;
end Behavioral;

