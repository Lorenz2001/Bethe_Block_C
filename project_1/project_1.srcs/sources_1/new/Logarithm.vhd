----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 29.10.2024 17:27:01
-- Design Name: 
-- Module Name: Logarithm - Behavioral
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

entity Logarithm is
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
end Logarithm;

architecture Behavioral of Logarithm is

    -- constants (scaled for 2^31)
    constant double_e_mass : std_logic_vector(msb downto lsb) :=  std_logic_vector(double_melectron);
    constant ionization : std_logic_vector(msb downto lsb) :=  std_logic_vector(ionization_scaled);
    
    --support signals
    signal current_enable,old_enable : std_logic;
    --beta_sqrt_rescaled 
    signal beta_sqrt_rescaled: std_logic_vector(msb downto lsb);
    
    --divisor signals
    signal num,den : std_logic_vector(msb downto lsb);
    signal result_division : std_logic_vector(39 downto 0);
    signal divisor_ready,dividend_ready : std_logic; --signal to check the presence of divisor and dividend (from div_gen)
    
    signal div_valid : std_logic; --asserted if division result is aviable;
    signal divisor_valid,dividend_valid : std_logic;
    
    --log signals
    signal log_arg : STD_LOGIC_VECTOR(msb DOWNTO lsb);  -- data forma signedfraction : 00._____
    signal enable_log : std_logic; 
      
    signal log_res : STD_LOGIC_VECTOR(msb+1 DOWNTO lsb); --sign.000000000
    
    signal valid_log : std_logic;
    
    
    --multiplication signals
    --num
    signal enable_num_mult : std_logic;
    --I_times_beta_sqrt
    signal enable_ion_mult : std_logic;
    signal I_times_beta_sqrt : std_logic_vector(2*msb+1 DOWNTO lsb);
    signal double_me_times_beta_sqrt : std_logic_vector(2*msb+1 DOWNTO lsb);
    
    
    -- subtraction signals
    signal sub_input : std_logic_vector(msb DOWNTO lsb);
    
    signal enable_sub : std_logic;
    signal sub_result :std_logic_vector(msb DOWNTO lsb);
    
    
    --shift signals
    signal enable_shift : std_logic;
    signal valid_shift : std_logic;
    signal shift_word : std_logic_vector(31 downto 0);
    signal shift_scale : integer;

component div_gen_0 IS
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
    m_axis_dout_tdata : OUT STD_LOGIC_VECTOR(39 DOWNTO 0)
  );
END component;


component Log is
  generic( msb : integer := 31;
           lsb : integer := 0);
  Port ( 
    clk : in std_logic;
    rst : in std_logic;
    
    arg : in STD_LOGIC_VECTOR(msb DOWNTO lsb);  -- data forma signedfraction : 00._____
    arg_valid : in std_logic; 
        
    log : out  STD_LOGIC_VECTOR(msb+1 DOWNTO lsb); --sign.000000000
    
    out_valid : out std_logic
    );
end component ;

component mult_gen_2 IS
  PORT (
    CLK : IN STD_LOGIC;
    A : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    B : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    CE : IN STD_LOGIC;
    P : OUT STD_LOGIC_VECTOR(63 DOWNTO 0)
  );
end component;

component c_addsub_0 is
  PORT (
    A : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    B : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    CLK : IN STD_LOGIC;
    CE : IN STD_LOGIC;
    S : OUT STD_LOGIC_VECTOR(31 DOWNTO 0)
  );
end component;


component ShiftUntilOne is
    generic( msb : integer := 31;
             lsb : integer := 0);
    Port ( 
           enable : STD_LOGIC;
           input_word : in  STD_LOGIC_VECTOR(msb downto lsb);
           output_word : out STD_LOGIC_VECTOR(msb downto lsb);
           valid_word : out std_logic;
           scale : out integer
          );
end component;



begin
 Main_process : process(clk,rst)
    begin
        if rising_edge (clk) then
           if(rst = '1') then
             dividend_valid <= '0';    
             divisor_valid <= '0';
             enable_log <= '0';
             enable_ion_mult <= '0';
             enable_num_mult <= '0';
             result <= (others => '0');
             out_valid <= '0'; 
                 
           else
           
           enable_ion_mult <= enable;
           enable_num_mult <= enable;
           
           old_enable <= current_enable;
           current_enable <= enable;
           
           beta_sqrt_rescaled <= '0' & beta_sqrt(msb downto lsb+1);
           
           if(old_enable = '1' and current_enable = '1') then -- if 2 clk ticks of enable, then i can use the results from multiplications
             den <= std_logic_vector(unsigned(ionization) - unsigned(I_times_beta_sqrt(2*msb+1 downto msb+1)));
             divisor_valid <= '1';
             num <= double_me_times_beta_sqrt(2*msb downto msb) ;
             dividend_valid <= '1';               
           else
             dividend_valid <= '0';    
             divisor_valid <= '0';        
           end if;
           
           if(div_valid = '1') then
             shift_word <= result_division(31 downto 0);
             enable_shift <= '1';
           else
             enable_shift <= '0';
           end if;
           
           if(valid_shift = '1') then
             enable_log <= '1';
           else
             enable_log <= '0';
           end if;
           
           
           if(valid_log = '1')then
             result <= log_res(31 downto 0); --manca +LN(2)*SCALE_SHIFT
             out_valid <= '1';
           else
             out_valid <= '0';
           end if;
             
           end if;
       end if;
    end process;
    
 Divison :  div_gen_0
  port map(
    aclk => clk,
    s_axis_divisor_tvalid => divisor_valid,
    s_axis_divisor_tready => divisor_ready,
    s_axis_divisor_tdata => den,
    s_axis_dividend_tvalid => dividend_valid,
    s_axis_dividend_tready => dividend_ready,
    s_axis_dividend_tdata => num,
    m_axis_dout_tvalid => div_valid,
    m_axis_dout_tuser => open,
    m_axis_dout_tdata => result_division
  );



Logarithm : Log
  Port map ( 
    clk => clk,
    rst => rst,
    
    arg => log_arg,
    arg_valid => enable_log, 
        
    log => log_res,
    
    out_valid => valid_log   
    );


numerator_mult : mult_gen_2
  Port Map (
    CLK => clk,
    A => double_e_mass,
    B => beta_sqrt_rescaled,
    CE => enable_num_mult,
    P => double_me_times_beta_sqrt
  );


I_mult_beta_sqrt : mult_gen_2
  Port Map(
    CLK => clk,
    A => ionization,
    B => beta_sqrt_rescaled,
    CE => enable_ion_mult,
    P => I_times_beta_sqrt
  );


shifter : ShiftUntilOne 
    Port Map ( 
           enable => enable_shift,
           input_word => shift_word,
           output_word => log_arg,
           valid_word => valid_shift,
           scale => shift_scale
          );


end Behavioral;


    
    
    
    
    
    
    
    
    