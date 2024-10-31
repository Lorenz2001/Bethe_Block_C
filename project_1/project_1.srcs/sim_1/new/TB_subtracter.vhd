----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 30.10.2024 19:30:06
-- Design Name: 
-- Module Name: TB_subtracter - Behavioral
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

entity TB_subtracter is
--  Port ( );
end TB_subtracter;

architecture Behavioral of TB_subtracter is

  signal clk,enable : std_logic;
  
  signal a,b,c : std_logic_vector(31 downto 0);
  

component c_addsub_0 is
  PORT (
    A : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    B : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    CLK : IN STD_LOGIC;
    CE : IN STD_LOGIC;
    S : OUT STD_LOGIC_VECTOR(31 DOWNTO 0)
  );
end component;
begin

Clock_Gen : process
    begin
     for i in 100 downto 0 loop
        clk <= '0';
        wait for 1 ns;
        clk <= '1';
        wait for 1 ns;
     end loop;      
    end process;
stim_process : process
    begin
      a <= x"00000256";
      b <= x"00000136";
      wait for 1.2 ns;
      a <= x"0000A256";
      b <= x"00000236";
      wait for 1.2 ns;
      a <= x"0000B256";
      b <= x"00000156";
      wait for 1.2 ns;
      a <= x"00000A56";
      b <= x"00000131";
      wait for 1.2 ns;
      a <= x"00000C56";
      b <= x"00000126";
      wait for 1.2 ns;
      a <= x"00000F56";
      b <= x"00000336";
      wait for 1.2 ns;
      a <= x"000002A6";
      b <= x"00000136";
      wait for 1.2 ns;
      
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
    

UUT : c_addsub_0 
  Port Map (
    A => a,
    B => b,
    CLK => clk,
    CE => enable
    S => c
  );

end Behavioral;
