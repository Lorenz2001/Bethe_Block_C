----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 25.10.2024 22:58:36
-- Design Name: 
-- Module Name: TB_Division - Behavioral
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
use  STD.textio.ALL;

entity TB_Division is

end TB_Division;

architecture Behavioral of TB_Division is
    
    constant clk_period : integer := 4; --250Mhz

    signal clk : std_logic := '0';
    signal rst : std_logic := '1';
    
    
    
    signal num,den : std_logic_vector(31 downto 0);
    signal res : std_logic_vector(39 downto 0);
    signal enable,divisor_ready,dividend_ready,en_res : std_logic;
    signal result : signed(31 downto 0);
   
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
       num <= std_logic_vector(to_signed(15,32));
       enable <= '0';
       wait for 3 ns;
       den <= std_logic_vector(to_signed(5,32)); 
       enable <= '1';
       wait for 10 ns;
       enable <= '0';
       wait for 50 ns;
       num <= std_logic_vector(to_signed(10,32));
       enable <= '0';
       wait for 3 ns;
       den <= std_logic_vector(to_signed(5,32)); 
       enable <= '1';
       wait for 10 ns;
       enable <= '0';
       wait for 40 ns;
       num <= std_logic_vector(to_signed(64,32));
       enable <= '0';
       wait for 3 ns;
       den <= std_logic_vector(to_signed(8,32)); 
       enable <= '1';
       wait for 10 ns;
       enable <= '0';
       wait for 50 ns;
      
    end process;
    
    
   -- Stim_process : process 
   --     file input_file : text open read_mode is "input.dat";  
   --     variable line_content : line;                          
   --     variable v_beta,v_dE : integer;                          
   -- begin
   --     while not endfile(input_file) loop
   --         readline(input_file, line_content);                
   --         read(line_content, v_beta);
   --         beta <= to_unsigned(32,v_beta);
   --         read(line_content, v_dE);
   --         dE <= to_unsigned(32,v_dE);                   
   --          report "Beta: " & integer'image(v_beta) & ", dE: " & integer'image(v_dE);  
   --         wait for 10 ns;
   --     end loop;
   --
   --     wait; 
   -- end process;
    
    
  UUT : div_gen_0
    PORT MAP (
    aclk => clk ,
    s_axis_divisor_tvalid => '1',
    s_axis_divisor_tready => divisor_ready,
    s_axis_divisor_tdata => den,
    s_axis_dividend_tvalid => enable,
    s_axis_dividend_tready => dividend_ready,
    s_axis_dividend_tdata => num,
    m_axis_dout_tvalid => en_res,
    m_axis_dout_tuser => open,
    m_axis_dout_tdata => res
  );
   
   
   result <= signed(res(33 downto 2));
end Behavioral;
