library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity HA is
    Port ( 
       a : in std_logic;
       b : in std_logic;
       
       sum : out std_logic;
       carry : out std_logic 
       );
end HA;

architecture Behavioral of HA is

begin
    sum <= a xor b;
    carry <= a and b;
end Behavioral;
