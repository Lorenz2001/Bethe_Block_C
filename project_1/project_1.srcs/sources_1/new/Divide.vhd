library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Divide is 
    generic (
        N : integer := 16);
        
    Port ( 
        numerator : in std_logic_vector(N-1 downto 0);
        denominator : in std_logic_vector(N-1 downto 0);
        
        result : in std_logic_vector(N-1 downto 0));
end Divide;

architecture Behavioral of Divide is
    

begin
        
    
end Behavioral;