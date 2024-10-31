----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 20.10.2024 23:31:28
-- Design Name: 
-- Module Name: Arg_1 - Behavioral
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
library Work;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use work.Material_Package.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;



-- Denominator of logarithm: (1-beta^2)*I
entity Arg_1 is
    generic( msb : integer := 31;
             lsb : integer := 0;
             scale : integer := 32
            ); 
  Port ( 
        
       clk : in std_logic;
       rst : in std_logic;
       
       beta_sqrt : in unsigned(msb downto lsb);
       enable : in std_logic;       
       
       result : out unsigned(msb downto lsb)
              
       );
end Arg_1;

    

architecture Behavioral of Arg_1 is
        
        
    component mult_gen_2 is
     PORT (
      CLK : IN STD_LOGIC;
      A : IN unsigned(msb DOWNTO lsb);
      B : IN unsigned(msb DOWNTO lsb);
      CE : IN STD_LOGIC;
      P : OUT unsigned(2*msb+1 DOWNTO lsb)
    );
    end component;    
    
    signal mult_CE : std_logic := '1';
    
    signal s_beta_sqrt : unsigned(msb downto lsb); 
    constant ionization: unsigned(msb downto lsb) := to_unsigned(msb+1,ionization_coeff);
    constant binary_I_X_one: unsigned(2*msb+1 downto lsb) :=  binary_ion_X_one;
    
    signal inv_gamma_sqrt : unsigned(msb downto 0);
    signal mult_res : unsigned(2*msb+1 downto lsb);   
    signal arg_1 : unsigned(msb downto lsb);
    signal sub : unsigned(2*msb+1 downto lsb); --support signal to subtract I-I*beta^2
    signal shifted_sub : unsigned(msb downto lsb);
begin
    
    s_beta_sqrt <= beta_sqrt;
    
    process(clk,rst)
    begin
      if rising_edge (clk) then
        if rst = '1' then 
           mult_CE <= '0';
           sub <= x"0000000000000001";
        else 
          if enable = '1' then   
           mult_CE <= '1';      
           sub <= binary_I_X_one - mult_res;
          else 
             mult_CE <= '1';      
             sub <= to_unsigned(2*msb+1,1);
          end if;
        end if;
      end if;   
    end process;
    
    
    
    
    I_times_beta_sqrt : mult_gen_2
    PORT MAP(
      CLK => clk, 
      A => ionization,
      B => s_beta_sqrt,
      CE => mult_CE,
      P => mult_res
    );
    
    result <=  sub(2*msb+1 downto lsb+scale);

end Behavioral;