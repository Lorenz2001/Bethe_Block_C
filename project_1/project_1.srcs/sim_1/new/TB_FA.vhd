library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity TB_FA is
end TB_FA;

architecture Behavioral of TB_FA is
   signal first  : std_logic;--: std_logic_vector(15 downto 0);
   signal second : std_logic;--: std_logic_vector(15 downto 0);
   signal result : std_logic;--: std_logic_vector(29 downto 0);
   signal c_out : std_logic;
   signal c_in : std_logic;
   
   constant test_a : std_logic_vector(7 downto 0) := "00001111";
   constant test_b : std_logic_vector(7 downto 0) := "00110011";
   constant test_c : std_logic_vector(7 downto 0) := "01010101";
   
   constant exp_c_out : std_logic_vector(7 downto 0) := "00010111";
   constant exp_sum : std_logic_vector(7 downto 0)   := "01101001";
   
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


    UUT : FA 
      Port Map( 
    first => first,
    second => second,
    c_in => c_in,
    
    sum => result,
    c_out => c_out
   );

test_FA: process
   begin 
   
    for i in 7 downto 0 loop
        first <= test_a(i);
        second <= test_b(i);
        c_in <= test_c(i);
        assert (c_out = exp_c_out(i))
            report "Errore nel c_out" severity error;
        assert (result = exp_sum(i))
            report "Errore nel sum" severity error;
        wait for 10 ns;
    end loop;
   end process;

end Behavioral;
