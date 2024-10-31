library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity TB_multiplier is
--  Port ( );
end TB_multiplier;

architecture Behavioral of TB_multiplier is


      signal  clk    : std_logic;
      signal  rst    : std_logic;
      signal  first  : std_logic_vector(15 downto 0);
      signal  second : std_logic_vector(15 downto 0);
      signal  result : std_logic_vector(31 downto 0);

   
   component Multiply is
         generic (
             N : integer);
        
        Port ( 
             clk : in std_logic;
             rst : in std_logic;
             
             first : in std_logic_vector(N-1 downto 0);
             second : in std_logic_vector(N-1 downto 0);
             
             result : out std_logic_vector((2*N-1) downto 0)
         );
   end component;
begin


    UUT : Multiply 
      Generic Map (N => 16)
      Port Map( 
             clk => clk,
             rst => rst,
             
             first => first, 
             second => second,
             
             result => result
         );
test_Multiply: process
   begin 
   
    
        first <=  "0000000001111011";
        second <= "0000000000011001";
        wait for 10 ns;
        first <=  "0000000001111011";
        second <= "0000000000000000";
        wait for 10 ns;
        first <=  "1111111111111111";
        second <= "1111111111111111";
        wait for 10 ns;
   end process;
    
end Behavioral;
