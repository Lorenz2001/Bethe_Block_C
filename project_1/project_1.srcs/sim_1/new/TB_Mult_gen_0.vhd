
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;


entity TB_Mult_gen_0 is
end TB_Mult_gen_0;

architecture Behavioral of TB_Mult_gen_0 is
    signal a,b,dd : std_logic_vector(31 downto 0);
    signal out_1, out_2 : std_logic_vector(63 downto 0);
    signal enable_1,enable_2 : std_logic;
    signal clk, rst : std_logic;
    type int_array is array (0 to 9) of unsigned(31 downto 0);
    constant inputs : int_array := (x"00000008",
                                    x"0000000F",
                                    x"00000171",
                                    x"2A569BCD",
                                    x"00000012",
                                    x"0000001A",
                                    x"00000017",
                                    x"00000009",
                                    x"0000000B",
                                    x"000268A3");
    component mult_gen_2 is
     PORT (
    CLK : IN STD_LOGIC;
    A : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    B : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    CE : IN STD_LOGIC;
    P : OUT STD_LOGIC_VECTOR(63 DOWNTO 0)
  );
  end component;
  
 -- component Power is
 --  generic( N : integer := 32;
 --          power : integer := 2);
 --  Port ( 
 --   clk : in std_logic;
 --   rst : in std_logic;
 --   enable : in std_logic;
 --   
 --   x: in std_logic_vector(N-1 downto 0);
 --   
 --   result : out std_logic_vector(power*N-1 downto 0)
 --   
 --   );
 --  end component;
        
begin
    
UUT_1 : mult_gen_2    
 Port Map (
    CLK => clk,
    A => a,
    B => b,
    CE => enable_1,
    P => out_1
  );

--UUT_2 : Power
--  generic map ( N => 32,
--           power => 2)
--   Port Map ( 
--    clk => clk,
--    rst => rst,
--    enable => enable_2,
--    
--    x => dd,
--    
--    result => out_2
--    
--    );
    
stim_process : process
begin
    for i in 0 to 9 loop
        a <= std_logic_vector(inputs(i));
        b <= std_logic_vector(inputs(i));
        dd <= std_logic_vector(inputs(i));
        --enable_1 <= '1';
        enable_2 <= '1';
        wait for 1.2 ns;
        --enable_1 <= '0';
        wait for 1.2 ns;
    end loop;
end process;

Clock_Gen : process
    begin
     for i in 100 downto 0 loop
        clk <= '0';
        wait for 1 ns;
        clk <= '1';
        wait for 1 ns;
     end loop;      
    end process;
    
Enable_Gen : process
    begin
     for i in 100 downto 0 loop
        enable_1 <= '1';
        wait for 1.2 ns;
        enable_1 <= '0';
        wait for 2.4 ns;
     end loop;      
    end process;
    


end Behavioral;
