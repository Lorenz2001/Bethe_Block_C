----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 01.10.2024 20:34:47
-- Design Name: 
-- Module Name: Log - Behavioral
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

entity Log is
  generic( msb : integer := 31;
           lsb : integer := 0); --both input output
  Port ( 
    clk : in std_logic;
    rst : in std_logic;
    
    arg : in STD_LOGIC_VECTOR(msb DOWNTO lsb);  -- data forma signedfraction : 00._____
    arg_valid : in std_logic; 
        
    log : out  STD_LOGIC_VECTOR(msb+1 DOWNTO lsb); --sign.000000000
    
    out_valid : out std_logic
    
    
    );
end Log;

architecture Behavioral of Log is
      
   signal enable_cordic, atan_valid, result_valid : std_logic;
   signal atan_res,atan_arg : STD_LOGIC_VECTOR(msb DOWNTO lsb);
   signal atan_input : STD_LOGIC_VECTOR(63 DOWNTO 0);
   signal result : STD_LOGIC_VECTOR(msb+1 downto lsb); --sign.000000000
  
  
   --SIGNAL FOR DIVISION
   signal num,den : std_logic_vector(msb downto lsb);
    signal result_division : std_logic_vector(63 downto 0);
    signal divisor_ready,dividend_ready : std_logic; --signal to check the presence of divisor and dividend (from div_gen)
    
    signal enable_division : std_logic; --asserted if division result is aviable;
    signal divisor_valid,dividend_valid : std_logic;  
   
   
  component cordic_0 is --note DATA FORMAT = signedFraction = 3bits.32Bit
    PORT (
    aclk : IN STD_LOGIC;
    s_axis_cartesian_tvalid : IN STD_LOGIC;
    s_axis_cartesian_tdata : IN STD_LOGIC_VECTOR(63 DOWNTO 0);
    m_axis_dout_tvalid : OUT STD_LOGIC;
    m_axis_dout_tdata : OUT STD_LOGIC_VECTOR(31 DOWNTO 0)
  );
  END component;

  component div_gen_1 is
    PORT (
    aclk : IN STD_LOGIC;
    s_axis_divisor_tvalid : IN STD_LOGIC;
    s_axis_divisor_tready : OUT STD_LOGIC;
    s_axis_divisor_tdata : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    s_axis_dividend_tvalid : IN STD_LOGIC;
    s_axis_dividend_tready : OUT STD_LOGIC;
    s_axis_dividend_tdata : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    m_axis_dout_tvalid : OUT STD_LOGIC;
    m_axis_dout_tuser : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
    m_axis_dout_tdata : OUT STD_LOGIC_VECTOR(63 DOWNTO 0)
  );
  end component;

   
   
begin
    --AGGIUNGERE CONTROLLO SULL'INPUT CHE DEVE ESSERE TALE CHE 0.5<arg<1 perchè torni il logaritmo
    
 process(clk,rst)
    begin
       if rising_edge (clk) then
           if(rst = '1') then
                enable_cordic <= '0';
                result <= (others => '0');
                atan_arg <= (others => '0');
                
                divisor_valid <= '0';
                dividend_valid <= '0';
                num <= (others => '0');
                den <= (others => '0');
                
           else
              if(enable_division = '1') then
                 enable_cordic <= '1';
                 atan_arg <= result_division(31 downto 0);
              else
               enable_cordic <= '0';
               atan_arg <= (others => '0');
              end if;
              
              if(arg_valid ='1') then
                divisor_valid <= '1';
                dividend_valid <= '1';
                num <= "11" & arg(29 downto 0);
                den <= "01" & arg(29 downto 0);
              else
                divisor_valid <= '0';
                dividend_valid <= '0';
              end if;
              
              
              if(atan_valid = '1') then
                result <= atan_res(32) & atan_res(30 downto 0) & '0';
                result_valid <= '1';
              else
               result <= (others => '0');
               result_valid <= '0';
              end if;
           
           end if;
       end if;
    end process;
    
 --process(atan_valid)
 --  begin
 --   if(atan_valid = '1') then
 --     result <= atan_res(msb downto lsb) & '0';
 --     result_valid <= '1';
 --   else
 --    result <= (others => '0');
 --    result_valid <= '0';
 --   end if;
 --end process;
    
    
atan : cordic_0
  port map(
    aclk => clk,
    s_axis_cartesian_tvalid => enable_cordic,
    s_axis_cartesian_tdata => atan_input,
    m_axis_dout_tvalid => atan_valid,
    m_axis_dout_tdata => atan_res
  );
 

Divison :  div_gen_1
  port map(
    aclk => clk,
    s_axis_divisor_tvalid => divisor_valid,
    s_axis_divisor_tready => divisor_ready,
    s_axis_divisor_tdata => den,
    s_axis_dividend_tvalid => dividend_valid,
    s_axis_dividend_tready => dividend_ready,
    s_axis_dividend_tdata => num,
    m_axis_dout_tvalid => enable_division,
    m_axis_dout_tuser => open,
    m_axis_dout_tdata => result_division
  );








 
atan_input <= atan_arg & "0100" & x"0000000";

log <= result;
    
end Behavioral;
