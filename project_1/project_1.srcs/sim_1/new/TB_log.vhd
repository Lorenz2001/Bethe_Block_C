----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 29.10.2024 22:01:37
-- Design Name: 
-- Module Name: TB_log - Behavioral
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
use IEEE.numeric_std.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity TB_log is
--  Port ( );
end TB_log;

architecture Behavioral of TB_log is
    
    signal clk : std_logic := '0';
    signal rst : std_logic := '0';
    
    signal arg : std_logic_vector(31 downto 0);
    signal arg_valid :std_logic; 
   
    signal result : std_logic_vector(32 downto 0); --sign.000000000
  
    signal out_valid :std_logic;

component Log is
  generic( msb : integer := 31;
           lsb : integer := 0);
  Port ( 
    clk : in std_logic;
    rst : in std_logic;
    
    arg : in std_logic_vector(msb downto lsb);
    arg_valid : in std_logic; 
        
    log : out  std_logic_vector(msb+1 downto lsb); --sign.000000000
    
    out_valid : out std_logic
    
    
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
    arg <= "00101000000000000000000000000000"; --0.625 => -0.4700036292
    arg_valid <= '1';
    wait for 50 ns;
    arg_valid <= '0';
    wait for 5 ns;
    arg <= "00" & "001101100100010110100001110010"; --0.212 => -1.551169004
    arg_valid <= '1';
    wait for 50 ns;
    arg_valid <= '0';
    wait for 5 ns;
    arg <= "00" & "010111100111011011001000101101"; --0.369 => -0.9969586349
    arg_valid <= '1';
    wait for 50 ns;
    arg_valid <= '0';
    wait for 5 ns;
    arg <= "00" & "110111100111011011001000101101"; --0.869 => -0.1404121537
    arg_valid <= '1';
    wait for 50 ns;
    arg_valid <= '0';
    wait for 5 ns;
    arg <= "00" & "101100101101111000000000110100"; --0.6987 => -0.3589338134
    arg_valid <= '1';
    wait for 50 ns;
    arg_valid <= '0';
    wait for 5 ns;
    
  end process;  
    
 UUT : Log 
  Port map ( 
    clk => clk,
    rst => rst,
    
    arg => arg,
    arg_valid => arg_valid,
        
    log => result, 
    
    out_valid => out_valid
    
    
    );


end Behavioral;
