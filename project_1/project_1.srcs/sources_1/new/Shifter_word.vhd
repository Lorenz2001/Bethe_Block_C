----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 31.10.2024 12:53:13
-- Design Name: 
-- Module Name: Shifter_word - Behavioral
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
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity ShiftUntilOne is
    generic( msb : integer := 31;
             lsb : integer := 0);
    Port ( enable : STD_LOGIC;
           input_word : in  STD_LOGIC_VECTOR(msb downto lsb);
           output_word : out STD_LOGIC_VECTOR(msb downto lsb);
           valid_word : out std_logic;
           scale : out integer
          );
end ShiftUntilOne;

architecture Behavioral of ShiftUntilOne is
begin
   
    process(input_word)
        variable temp_word : STD_LOGIC_VECTOR(msb downto lsb);
        variable cnt : integer := 0;
    begin
       if (enable = '1') then
       valid_word <= '0';
        temp_word := input_word;
        while temp_word(31) /= '1' loop
            temp_word := temp_word(msb-1 downto lsb) & '0';
            cnt := cnt +1;
        end loop;
        output_word <= temp_word;
        valid_word <= '1';
        scale <= cnt;
      else
       valid_word <= '0';
      end if;
    end process;
end Behavioral;
