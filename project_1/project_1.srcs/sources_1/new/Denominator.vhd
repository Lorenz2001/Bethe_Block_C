----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 25.10.2024 20:08:43
-- Design Name: 
-- Module Name: Denominator - Behavioral
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
library work;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.ALL;
use work.Material_Package.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity Denominator is
  Generic( msb : integer :=21;
           lsb : integer := 0);
  Port ( 
    clk : in std_logic;
    rst : in std_logic;
    
    enable : in std_logic;
    
    beta_sqrt : in unsigned(msb downto lsb);
    
    scale : in integer;
    result : out unsigned(msb downto lsb)
    
  );
end Denominator;

architecture Behavioral of Denominator is

component arg_1 is
  generic( msb : integer;
             lsb : integer;
             scale : integer
            ); 
  Port ( 
        
       clk : in std_logic;
       rst : in std_logic;
       
       beta_sqrt : in unsigned(msb downto lsb);
       enable : in std_logic;       
       
       result : out unsigned(msb downto lsb)
              
       );
end component;

component mult_gen_2 is
     PORT (
      CLK : IN STD_LOGIC;
      A : IN unsigned(msb DOWNTO lsb);
      B : IN unsigned(msb DOWNTO lsb);
      CE : IN STD_LOGIC;
      P : OUT unsigned(2*msb+1 DOWNTO lsb)
    );
    end component;    
    
    
component Log is
  generic( msb : integer;
           lsb : integer);
  Port ( 
    clk : in std_logic;
    rst : in std_logic;
    
    arg : in unsigned(msb downto lsb);
    enable : in std_logic; -- TO INTEGRATE
        
    log : out  unsigned(msb downto lsb)
      
    );
end component;

    
  signal s_en : std_logic;
  signal s_beta : unsigned(msb downto lsb);
   
  
  signal res_arg_1,res_arg_2,res_log_1,res_log_2, parenthesis : unsigned(msb downto lsb);
  signal res_mult, res_denominator : unsigned(2*msb+1 downto lsb);
  
  signal en_log_1, en_log_2, last_mult_CE : std_logic;

begin
 
 
 s_beta <= beta_sqrt;
 
 main_process: process(clk,rst)
 begin
    if rising_edge (clk) then
        if rst = '1' then
        else
                 
                   
        end if;
    end if;
    
 end process;
 
 
 
  Unit_arg_1 : arg_1
    Generic Map( msb => msb,
             lsb => lsb,
             scale => scale
            ) 
  Port Map ( 
        
       clk => clk,
       rst => rst,
       enable => enable,
       beta_sqrt => s_beta,
       result => res_arg_1
       );   
 
 Unit_arg_2 : mult_gen_2
    PORT MAP(
      CLK => clk, 
      A => double_melectron,
      B => beta_sqrt,
      CE => enable,
      P => res_mult
    );

  Log_1 : Log 
  Generic Map( msb => msb,
           lsb => lsb)
  Port Map ( 
    clk => clk,
    rst => rst,
    
    arg => res_arg_1,
    enable => en_log_1,
        
    log => res_arg_1
      
    );
    
  Log_2 : Log 
  Generic Map( msb => msb,
           lsb => lsb)
  Port Map ( 
    clk => clk,
    rst => rst,
    
    arg => res_arg_2,
    enable => en_log_2,
        
    log => res_arg_2
      
    );
  
    
    
    Result_Denominator : mult_gen_2
    PORT MAP(
      CLK => clk, 
      A => thick_x_K_x_rho,
      B => parenthesis,
      CE => last_mult_CE,
      P => res_denominator
    );
    
    
    
end Behavioral;
