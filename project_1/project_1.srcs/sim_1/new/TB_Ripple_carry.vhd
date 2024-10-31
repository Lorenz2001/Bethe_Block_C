----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 07.10.2024 12:37:37
-- Design Name: 
-- Module Name: TB_Ripple_carry - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
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
entity TB_Ripple_carry is
--  Port ( );
end TB_Ripple_carry;

architecture Behavioral of TB_Ripple_carry is
    signal first : std_logic_vector(15 downto 0); 
    signal second : std_logic_vector(15 downto 0);
    signal c_in : std_logic;                       
                             
    signal c_out : std_logic;                     
    signal sum : std_logic_vector(15 downto 0)  ;
     

    component Ripple_carry_N is
        generic( N : integer);
        Port ( 
             first : in std_logic_vector(N-1 downto 0);
             second : in std_logic_vector(N-1 downto 0);
             c_in : in std_logic;
             
             c_out : out std_logic;
             sum : out std_logic_vector(N-1 downto 0)
        
        );
    end component;
begin
   UUT : Ripple_carry_N
   
     Generic Map( N  => 16)                            
     Port Map(                                            
      first => first,
      second => second,
      c_in => c_in,
             
      c_out => c_out, 
      sum => sum
                                                   
 );      
 
 stim_process : process
 begin
    first <=  "0000000001111011";
    second <= "0000000000001111";
    c_in <= '0';
    wait for 1.6 ns;
 end process;                                          

end Behavioral;
