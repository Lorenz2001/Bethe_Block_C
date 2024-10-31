library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use work.BB_Package.all;

entity Multiply is 
    generic (
        N : integer := 16);
        
    Port ( 
        clk : in std_logic;
        rst : in std_logic;
        
        first : in std_logic_vector(N-1 downto 0);
        second : in std_logic_vector(N-1 downto 0);
        
        result : out std_logic_vector((2*N)-1 downto 0));
end Multiply;

architecture Behavioral of Multiply is

   type array_of_vector is array (N-1 downto 0) of std_logic_vector(N-1 downto 0);
   signal a, b : std_logic_vector(N-1 downto 0);
   signal semi_prod : array_of_vector := (others => (others => '0'));
   signal support : array_of_vector := (others => (others => '0'));
   signal supp_sum : array_of_vector := (others => (others => '0'));
   signal c : std_logic_vector (N-1 downto 0);
   
   signal carrys : std_logic_vector(N downto 0) := (others => '0');
   
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
   
   process(first,second)
   --variable c_v : std_logic_vector ((2*N-1) downto 0) := (others => '0');
   begin
      --  if rising_edge(clk) then
           -- if rst = '1' then
           --     a <= (others => '0');
           --     b <= (others => '0');
           --     --c <= (others => '0');
           -- else
               -- a <= first;
               -- b <= second;
                for i in N-1 downto 0 loop
                   for j in N-1 downto 0 loop 
                            semi_prod(i)(j) <= first(i) AND second(j);
                   end loop;
                end loop;
                
               
          --  end if;
        --end if;
   end process;    
   
   
   supp_sum(0) <= semi_prod(0);
   carrys(0) <= '0'; 
   
   RC_generate : for i in N-2 downto 0 generate
        support(i) <= carrys(i) & supp_sum(i)(N-1 downto 1);
        RC : Ripple_Carry_N
            Generic Map( N => N)                            
            Port Map(                                            
             first => support(i),
             second => semi_prod(i+1),
             c_in => '0',
                    
             c_out => carrys(i+1), 
             sum => supp_sum(i+1)                   
            );      
   end generate;
   
   --lsb : 
    --result(0) <= semi_prod(0)(0);
   reg_bits_generator : for i in N-2 downto 0 generate
        result(i) <= supp_sum(i)(0);
   end generate;
   
   other_bits : 
    result(2*N-2 downto N-1) <= supp_sum(N-1);
   msb : 
    result(2*N-1) <= carrys(N-1);
   
   
end Behavioral;