----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 19.10.2024 15:25:06
-- Design Name: 
-- Module Name: Bethe_Block - Behavioral
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

entity Bethe_Block is
    generic( msb : integer := 31;
             lsb : integer := 0);            
    );
             
             
             
             
  Port ( 
    clk : in std_logic;
    rst : in std_logic;
    
    dE : in unsigned(msb downto lsb);
    beta : in unsigned(msb downto lsb);
    
    squared_charge : out unsigned(msb downto lsb);    
     
    );
end Bethe_Block;

architecture Behavioral of Bethe_Block is


  component Power is
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
  end component;
    
    

begin


end Behavioral;
