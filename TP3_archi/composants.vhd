---ALU du TP1 en version comportementale

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

entity ALU is
  port (
    R_e0: in STD_LOGIC_VECTOR(7 downto 0);
    R_e1: in STD_LOGIC_VECTOR(7 downto 0);
    Op: in STD_LOGIC_VECTOR(1 downto 0);
    R_s: out STD_LOGIC_VECTOR(7 downto 0)
    );
end entity;

architecture arch_ALU_comportemental of ALU is
begin
  process(Op, R_e0, R_e1)
  begin
    if R_e0 = "UUUUUUUU" or R_e1 = "UUUUUUUU" then
      R_s <= "UUUUUUUU";
    else
      if Op = "00" then
        R_s <= std_logic_vector(to_unsigned(to_integer(unsigned(R_e0)) + to_integer(unsigned(R_e1)), R_s'length));
      elsif Op = "01" then
        R_s <= std_logic_vector(to_signed(to_integer(unsigned(R_e0)) - to_integer(unsigned(R_e1)), R_s'length));
      elsif Op = "10" then
        R_s <= R_e0 and R_e1;
      else
        R_s <= R_e1;
      end if;
    end if;
  end process;
end architecture;


---Bascule D du TP2 en version comportementale
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity bascule_D is
  port (
    e: in STD_LOGIC;
    clk: in STD_LOGIC;
    rst: in STD_LOGIC;
    set: in STD_LOGIC;
    s: out STD_LOGIC
    );
end entity;

architecture arch_bascule_D of bascule_D is
begin
  process(clk, rst, set)
  begin
    if rst = '0' then
      s <= '0';
    elsif set = '0' then
      s <= '1';
    elsif rising_edge(clk) then
      s <= e;
    end if;
  end process;
end architecture;

---Registre 8 bits du TP2 en version comportementale

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity r8bits is
  port(
    R_in: in STD_LOGIC_VECTOR(7 downto 0);
    WR: in STD_LOGIC;
    rst: in STD_LOGIC;
    clk: in STD_LOGIC;
    R_out: out STD_LOGIC_VECTOR(7 downto 0)
    );
end entity;

architecture arch_r8bits_comp of r8bits is
begin
  process(clk, rst)
  begin
    if rst = '0' then
      R_out <= "00000000";
    elsif rising_edge(clk) then
      if WR = '1' then
        R_out <= R_in;
      end if;
    end if;
  end process;
end architecture;

---Banc de registres du TP2 en version comportementale
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

entity banc is
  port(
    reg_0_id: in STD_LOGIC_VECTOR(2 downto 0);
    reg_1_id: in STD_LOGIC_VECTOR(2 downto 0);
    reg_write_val: in STD_LOGIC_VECTOR(7 downto 0);
    WR: in STD_LOGIC;
    clk: in STD_LOGIC;
    rst: in STD_LOGIC;
    reg_0_val: out STD_LOGIC_VECTOR(7 downto 0);
    reg_1_val: out STD_LOGIC_VECTOR(7 downto 0)
    );
end entity;

architecture arch_banc_comportemental of banc is
  type reg_array is array (0 to 7) of STD_LOGIC_VECTOR(7 downto 0);
  signal regs: reg_array;
begin
  -- 1 process for WR
  process(clk, rst)
  begin
    if rst = '0' then
      for i in 0 to 7 loop
        regs(i) <= "00000000";
      end loop;
    
    elsif rising_edge(clk) then 
      if WR = '1' then
        regs(to_integer(unsigned(reg_0_id))) <= reg_write_val;
      end if;
    end if;
  end process;

  -- 1 process for Reads
  process(reg_0_id, reg_1_id, regs)
  begin
    if reg_0_id = "UUU" or reg_1_id = "UUU" then
      reg_0_val <= "UUUUUUUU";
      reg_1_val <= "UUUUUUUU";
    else
      reg_0_val <= regs(to_integer(unsigned(reg_0_id)));
      reg_1_val <= regs(to_integer(unsigned(reg_1_id)));
    end if;
  end process;
end architecture;

