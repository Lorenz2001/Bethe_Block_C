----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 30.10.2024 20:40:01
-- Design Name: 
-- Module Name: TB_Logarithm - Behavioral
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

entity TB_Logarithm is
--  Port ( );
end TB_Logarithm;

architecture Behavioral of TB_Logarithm is

    signal clk : std_logic := '0';
    signal rst : std_logic := '0';
    
    signal enable :std_logic;                        
                                               
    signal beta_sqrt: std_logic_vector(31 downto 0);
                                                   
    signal result : std_logic_vector(31 downto 0);
    signal out_valid : std_logic;                     
    
    
    
    
    
    
    
component Logarithm is
    generic( msb : integer := 31;
                 lsb : integer := 0;
                 scale : integer := 32
                ); 
      Port ( 
        clk : in std_logic;
        rst : in std_logic;
        enable : in std_logic;
        
        beta_sqrt: in std_logic_vector(msb downto lsb);
        
        result : out std_logic_vector(msb downto lsb);
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
      beta_sqrt <= x"0583A53B";
      enable <= '1';
      wait for 15 ns;
      enable <= '0';
      wait for 1 ns;
      beta_sqrt <= x"0DF3B645";
      enable <= '1';
      wait for 15 ns;
      enable <= '0';
      wait for 1 ns;
      beta_sqrt <= x"10BE0DED";
      enable <= '1';
      wait for 15 ns;
      enable <= '0';
      wait for 1 ns;
      beta_sqrt <= x"0D59B3D0";
      enable <= '1';
      wait for 15 ns;
      enable <= '0';
      wait for 1 ns;
      beta_sqrt <= x"0E136E71";
      enable <= '1';
      wait for 15 ns;
      enable <= '0';
      wait for 1 ns;
      
      
   end process;

UUT : Logarithm
 Port Map ( 
        clk => clk,
        rst => rst,
        enable => enable,
        
        beta_sqrt => beta_sqrt,
        
        result => result,
        out_valid => out_valid
        
        );


end Behavioral;
