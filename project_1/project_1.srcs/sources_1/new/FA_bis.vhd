library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity FA is
  Port ( 
    first : in std_logic;
    second : in std_logic;
    c_in : in std_logic;
    
    sum : out std_logic; 
    c_out : out std_logic 
   );
end FA;

architecture Behavioral of FA is
    signal c_1,c_2 : std_logic;
    signal s_1,s_2 : std_logic;
   component HA is 
   Port ( 
       a : in std_logic;
       b : in std_logic;
       
       sum : out std_logic;
       carry : out std_logic 
       );
   end component; 
begin
  
  Bit_sum : HA 
    Port Map (
       a => first,
       b => second,
       
       sum => s_1,
       carry => c_1 
       );
       
   Carry_sum : HA
     Port Map (
       a => c_in,
       b => s_1,
       
       sum => s_2,
       carry => c_2 
       );
       
    output :
       sum <= s_2;
       c_out <= c_1 OR c_2;
 

end Behavioral;
