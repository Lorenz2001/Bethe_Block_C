----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 08.10.2024 17:34:09
-- Design Name: 
-- Module Name: Power - Behavioral
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

entity Power is
  generic(
           N : integer := 32;
           power : integer := 2;
           scale : integer := 32);
  Port ( 
    clk : in std_logic;
    rst : in std_logic;
    enable : in std_logic;
    
    x: in std_logic_vector(N-1 downto 0);
    
    result : out std_logic_vector(N-1 downto 0)
    
    );
end Power;

architecture Behavioral of Power is
    
    signal res : std_logic_vector(power*N-1 downto 0);
    signal input : std_logic_vector(N-1 downto 0);
    signal en : std_logic;


component mult_gen_2 is
     PORT (
    CLK : IN STD_LOGIC;
    A : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    B : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    CE : IN STD_LOGIC;
    P : OUT STD_LOGIC_VECTOR(63 DOWNTO 0)
  );
         
end component;


begin
    
    
    input <= x;
    
    
    process(clk,rst)
    begin
        if rising_edge(clk) then
          
           if (rst = '1') then
            en <= '0';
            res <= (others => '0');
            else 
             en <= '1';
            end if;
        end if;
    end process;
    
    multi : mult_gen_2
    Port Map(
    CLK  => clk,
    A => input,
    B => input,
    CE => en,
    P => res
  );
  
  result <= res(2*N-1 downto scale);

end Behavioral;
