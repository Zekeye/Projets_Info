-- Architecture 2. Sujet de TP 3 (seances 5 et 6).
-- Implementation d'un processeur simplifié
-- Author: T. Carle (thomas.carle@irit.fr)


-- I. Assemblage de l'ALU et du banc de registres
-- I.0. MUX 2 -> 1 8 bits
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity MUX2_1_8 is
  port (
    e0: in STD_LOGIC_VECTOR(7 downto 0);
    e1: in STD_LOGIC_VECTOR(7 downto 0);
    c: in STD_LOGIC;
    o: out STD_LOGIC_VECTOR(7 downto 0)
    );
end entity;

architecture arch_MUX2_1_8 of MUX2_1_8 is
begin
  o <= e1 when c = '1'
       else e0;
end architecture;
-------------------------------------------------------------------

-- I.1. processeur
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity proc_v0 is
  port (
    op: in STD_LOGIC_VECTOR(1 downto 0);
    reg_0_id: in STD_LOGIC_VECTOR(2 downto 0);
    reg_1_id: in STD_LOGIC_VECTOR(2 downto 0);
    rst: in STD_LOGIC;
    clk: in STD_LOGIC;
    WR_bank: in STD_LOGIC
    );
end entity;

architecture proc_v0_struct of proc_v0 is
  signal mux_out, alu_out, bank_out_0, bank_out_1, mux_in_5_3 : STD_LOGIC_VECTOR(7 downto 0);
  signal Op_out_and : STD_LOGIC;
  
  begin
   mux_in_5_3 <= "00000" & reg_1_id;
   Op_out_and <= Op(0) and Op(1);
      mu: entity work.MUX2_1_8
	port map(e0 => bank_out_1,
		 e1 => mux_in_5_3,
		 c => Op_out_and,
		 o => mux_out);
		 
      al : entity work.ALU
        port map(R_e0 => bank_out_0,
                 R_e1 => mux_out,
                 R_s => alu_out,
                 Op => op);

      ba : entity work.banc
        port map(reg_0_id => reg_0_id,
                 reg_1_id => reg_1_id,
                 reg_write_val => alu_out,
                 WR => WR_bank,
                 clk => clk,
                 rst => rst,
                 reg_0_val => bank_out_0,
                 reg_1_val => bank_out_1);
end architecture;

-------------------------------------------------------------------

--II. Ajout d'un sequenceur pour obtenir le processeur simplifie
--II.1. Sequenceur
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity sequencer is
  port (
    init : in STD_LOGIC;
    clk: in STD_LOGIC;
    WR_instr: out STD_LOGIC;
    WR_bank: out STD_LOGIC
    );
end entity;

architecture sequencer_struct of sequencer is
  signal b_out_1, b_out_2:STD_LOGIC;
  begin
    
    baun : entity work.bascule_D
      port map(e => b_out_2,
               clk => clk,
	       rst => init,
	       set => init,
               s=> b_out_1);
    
    badeux : entity work.bascule_D
      port map(e=>b_out_1,
               clk=>clk,
               rst => init,
               set => init,
               s => b_out_2);
end architecture;
               

-------------------------------------------------------------------
--II.2. Assemblage du processeur
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity proc_v1 is
  port (
    instr: in STD_LOGIC_VECTOR(7 downto 0);
    Init: in STD_LOGIC;
    rst: in STD_LOGIC;
    clk: in STD_LOGIC
    );
end entity;

architecture arch_proc_v1 of proc_v1 is 
signal WR_bank_out: STD_LOGIC;
signal WR_instr_out: STD_LOGIC;
signal R_out_reg: STD_LOGIC_VECTOR(7 downto 0);
  begin
  
  se: entity work.sequencer
     port map(init => Init,
              clk => clk,
              WR_instr => WR_instr_out,
              WR_bank => WR_bank_out);

  re: entity work.r8bits
     port map( R_in => instr,
               WR => WR_instr_out,
               rst => '1',
               clk => clk,
               R_out => R_out_reg);

  pr: entity work.proc_v0
     port map(op => R_out_reg(7 downto 6),
              reg_0_id => R_out_reg(5 downto 3),
              reg_1_id => R_out_reg(2 downto 0),
              rst => rst,
              clk => clk,
              WR_bank => WR_bank_out);
end architecture;
               
-------------------------------------------------------------------
