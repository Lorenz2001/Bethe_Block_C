----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 07.10.2024 12:15:25
-- Design Name: 
-- Module Name: Ripple_Carry_N - Behavioral
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity Ripple_Carry_N is
    generic( N : integer := 8);
      Port ( 
        first : in std_logic_vector(N-1 downto 0);
        second : in std_logic_vector(N-1 downto 0);
        c_in : in std_logic;
        
        c_out : out std_logic;
        sum : out std_logic_vector(N-1 downto 0)
        
        );
end Ripple_Carry_N;

architecture Behavioral of Ripple_Carry_N is

 signal carrys : std_logic_vector(N downto 0) := (others => '0');

 component FA is                 
      Port (                     
           first : in std_logic; 
           second : in std_logic;
           c_in : in std_logic;  
                                 
           sum : out std_logic;  
           c_out : out std_logic 
      );                         
 end component;                  



begin

    initial_carry:
        carrys(0) <= c_in;
    FA_generator : 
        for i in N-1 downto 0 generate
            Full_adder : FA 
                Port Map(
                  first => first(i),
                  second => second(i),
                  c_in => carrys(i), 
                                        
                  sum => sum(i),
                  c_out => carrys(i+1)
                );
        end generate;
    
    c_out <= carrys(N);


end Behavioral;
