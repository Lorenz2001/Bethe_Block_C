library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity vector_adder is
  generic (
        N : integer := 64); -- N deve essere PARI
  Port (
      vector : in std_logic_vector(N-1 downto 0);
      
      sum : out std_logic;
      carry : out natural
       );
end vector_adder;

architecture Behavioral of Vector_adder is
    signal add_on_elements : std_logic_vector(N/2-1 downto 0);
    signal s_c : std_logic_vector(N/2-1 downto 0);
    
component half_adder is
    Port ( 
       a : in std_logic;
       b : in std_logic;
       
       sum : out std_logic;
       carry : out std_logic 
       );
end component;

begin
    
Adder_generate : 

    for i in 0 to N/2-1 generate
        couple_adder : half_adder Port map(a => vector(2*i), b => vector(2*i+1), sum => add_on_elements(i), carry => s_c(i)); 
    end generate;
    
    
    
end Behavioral;
