-- Architecture 2. Sujet de TP 2 (seances 3 et 4).
-- Implementation d'un banc de registres
-- Author: T. Carle (thomas.carle@irit.fr)


-- I. Decodeur 3 -> 8
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity decodeur3_8 is
  port (
    e: in STD_LOGIC_VECTOR(2 downto 0);
    s: out STD_LOGIC_VECTOR(7 downto 0)
    );
end entity;

architecture decodeur3_8_fd of decodeur3_8 is
  begin
	s(0) <= not e(0) and not e(1) and not e(2);
	s(1) <= e(0) and not e(1) and not e(2);
	s(2) <= not e(0) and e(1) and not e(2);
	s(3) <= e(0) and e(1) and not e(2);
	s(4) <= not e(0) and not e(1) and e(2);
	s(5) <= e(0) and not e(1) and e(2);
	s(6) <= not e(0) and e(1) and e(2);
	s(7) <= e(0) and e(1) and e(2);
  end architecture decodeur3_8_fd;
		

-------------------------------------------------------------------

-- II. Registre 8 bits lecture/ecriture paralleles
--II.1. Bascule D
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

--II.2. Multiplexeur 2->1

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity mux2_1 is
  port (
    e: in STD_LOGIC_VECTOR(1 downto 0);
    c: in STD_LOGIC;
    s: out STD_LOGIC
    );
end entity;

architecture mux_2_1_fd of mux2_1 IS
  begin
    s<=e(1) when (c='0') else e(0);
  end architecture mux_2_1_fd;

-- II.3. Registre 8 bits
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

architecture r8bits_struct of r8bits is
  signal D_out: STD_LOGIC_VECTOR(7 downto 0);
  signal mux_out: STD_LOGIC_VECTOR(7 downto 0);

  begin

    reg: for i in 0 to 7 generate
	muxi: entity work.mux2_1
		port map(e(0)=>R_in(i),
			e(1)=>D_out(i),
			c=>WR,
			s=>mux_out(i));
			
	basc_di: entity work.bascule_D
		port map(e=>mux_out(i),
			clk=>clk,
			rst=>rst,
			set=>'1',
			S=>D_out(i));
	R_out(i)<=D_out(i);
	end generate reg;
  end architecture r8bits_struct;
			
-------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

--III. Porte 3 etats
entity p3e is
  port(
    a: in STD_LOGIC_VECTOR(7 downto 0);
    b: in STD_lOGIC;
    c: out STD_LOGIC_VECTOR(7 downto 0)
    );
end entity;

architecture p3e_fd of p3e is
  begin
    porte: for i in 0 to 7 generate
      c(i)<= a(i) when b = '1' else
             'Z' when b = '0' else
             'X';
    end generate porte;
end architecture p3e_fd;


-------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


--IV. Banc de 8 registres 8 bits
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
        
architecture arch_banc of banc is
  type reg_array is array (0 to 7) of STD_LOGIC_VECTOR(7 downto 0);
  signal dec_out1, dec_out2:STD_LOGIC_VECTOR(7 downto 0);
  signal WR_out_and: STD_LOGIC_VECTOR(7 downto 0);
  signal array_reg_out : reg_array;

begin
  re: for i in 0 to 7 generate
  
    WR_out_and(i)<=dec_out1(i) and WR;
  
    de_un : entity work.decodeur3_8
           port map(e=>reg_0_id,
	       	    s=>dec_out1);
  
    de_deux : entity work.decodeur3_8
	      port map(e=>reg_1_id,
		       s=>dec_out2);

    rhuit : entity work.r8bits
	    port map(R_in=>reg_write_val,
		     WR=>WR_out_and(i),
		     rst=>rst,
		     clk=>clk,
		     R_out=>array_reg_out(i));

    p3eun : entity work.p3e
	   port map( a=>array_reg_out(i),
	             b=>dec_out1(i),
		     c=>reg_0_val);
  
    p3e_deux : entity work.p3e
	       port map( a=>array_reg_out(i),
	  	         b=>dec_out2(i),
		         c=>reg_1_val);

  END GENERATE re;
  
end architecture;
