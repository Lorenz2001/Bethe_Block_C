-- MATERIAL PROPERTIES --



library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

package Material_Package is
    --Generic_consts
    constant double_melectron : unsigned(31  downto 0) := x"82D0E560"; --SCALED for 2^31
    
    --SILICON
    constant A : integer := 28;
    constant Z : integer := 14;
    constant density : integer := 232; --g/cm^-3 *100
    constant ionization_coeff : integer := 16; --MeV *10^6;
    
    constant ionization_scaled : unsigned(31 downto 0) := x"00008638"; --scaled for 2^31
    constant  thick_x_K_x_rho : unsigned(21 downto 0) := "00" & x"5B306";
end package;

package body Material_Package is
 
end package body;