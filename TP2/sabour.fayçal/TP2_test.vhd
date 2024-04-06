--I. Decodeur
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity decodeur3_8_test is
end entity;

architecture arch_decodeur3_8_test of decodeur3_8_test is
  signal et: STD_LOGIC_VECTOR(2 downto 0);
  signal st: STD_LOGIC_VECTOR(7 downto 0);
begin

  de: entity work.decodeur3_8
    port map (
      e => et,
      s => st
      );

  process
  begin
    et <= "000";
    wait for 5 ns;
    assert st = "00000001";

    et <= "001";
    wait for 5 ns;
    assert st = "00000010";

    et <= "010";
    wait for 5 ns;
    assert st = "00000100";

    et <= "011";
    wait for 5 ns;
    assert st = "00001000";

    wait;
  end process;
end architecture;
------------------------------------------------------------
--II. Registre 8 bits 
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity r8bits_test is
end entity;

architecture arch_r8bits_test of r8bits_test is
  signal R_int, R_outt: STD_LOGIC_VECTOR(7 downto 0);
  signal WRt, rstt, clkt: STD_LOGIC;
begin

  r8: entity work.r8bits
    port map (
      R_in => R_int,
      R_out => R_outt,
      WR => WRt,
      rst => rstt,
      clk => clkt
      );

  process
  begin
    R_int <= "10101010";
    rstt <= '1';
    clkt <= '0';
    WRt <= '0';
    
    rstt <= '0';
    wait for 5 ns;
    assert R_outt <= "00000000";
    
    rstt <= '1';
    wait for 5 ns;

    clkt <= '1';
    wait for 5 ns;
    assert R_outt = "10101010";

    wait;
  end process;
end architecture;
------------------------------------------------------------
--III. Porte 3 etats
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity p3e_test is
end entity;

architecture arch_p3e_test of p3e_test is
  signal at, ct: STD_LOGIC_VECTOR(7 downto 0);
  signal bt: STD_LOGIC;
begin

  po: entity work.p3e
    port map (
      a => at,
      b => bt,
      c => ct
      );

  process
  begin
    at <= "00000001";
    bt <= '1';
    wait for 5 ns;
    assert ct = "00000001";

    bt <= '0';
    wait for 5 ns;
    assert ct = "ZZZZZZZZ";

    wait;
  end process;
end architecture;
------------------------------------------------------------
--IV. Banc de registres
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity banc_test is
end banc_test;

architecture arch_banc_test of banc_test is
  signal reg_0_valt, reg_1_valt, reg_write_valt: STD_LOGIC_VECTOR(7 downto 0);
  signal reg_0_idt, reg_1_idt: STD_LOGIC_VECTOR(2 downto 0);
  signal WRt, clkt, rstt: STD_LOGIC;

begin
  ba: entity work.banc 
    port map (
      reg_0_id => reg_0_idt,
      reg_1_id => reg_1_idt,
      reg_write_val => reg_write_valt,
      WR => WRt,
      clk => clkt,
      rst => rstt,
      reg_0_val => reg_0_valt,
      reg_1_val => reg_1_valt
      );

  process
  begin
    reg_0_idt <= "000";
    reg_1_idt <= "000";
    reg_write_valt <= "00000101";
    WRt <= '0';
    clkt <= '0';
    rstt <= '0';
    wait for 5 ns;
    assert reg_0_valt = "00000000";
    assert reg_1_valt = "00000000";

    rstt <= '1';
    wait for 5 ns;
	
    reg_0_idt <= "010";
    WRt <= '1';
		
    wait for 5 ns;
    clkt <= '1';
    wait for 5 ns;
    assert reg_0_valt = "00000101";
    assert reg_1_valt = "00000000";

    clkt <= '0';
    WRt <= '0';

    reg_0_idt <= "101";
    reg_1_idt <= "010";
    wait for 5 ns;
    assert reg_0_valt = "00000000";
    assert reg_1_valt = "00000101";

    wait;
  end process;
end architecture;
