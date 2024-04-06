-- Architecture 2. Sujet de TP 3 (seances 5 et 6).
-- Implementation d'un processeur simplifié -- banc de test
-- Author: T. Carle (thomas.carle@irit.fr)

-- I. Processeur v0
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity proc_v0_test is
end entity;

architecture arch_proc_v0_test of proc_v0_test is

  signal op_in : STD_LOGIC_VECTOR(1 downto 0);
  signal reg_0_id, reg_1_id: STD_LOGIC_VECTOR(2 downto 0);
  signal rst, clk, WR_bank: STD_LOGIC;

begin
  proc: entity work.proc_v0
    port map(op_in, reg_0_id, reg_1_id, rst, clk, WR_bank);

  process
  begin
    -- Initialize all registers to 0
    rst <= '0';
    clk <= '0';
    reg_0_id <= "000";
    reg_1_id <= "000";
    WR_bank <= '0';
    wait for 5 ns;
    rst <= '1';
    wait for 5 ns;

    --MOV R0, #4
    op_in <= "11";
    reg_0_id <= "000";
    reg_1_id <= "100";
    wait for 5 ns;
    clk <= '1';
    wait for 5 ns;
    clk <= '0';
    WR_bank <= '1';
    wait for 5 ns;
    clk <= '1';
    wait for 5 ns;
    clk <= '0';
    WR_bank <= '0';

    -- MOV R2, #3
    reg_0_id <= "010";
    reg_1_id <= "011";
    wait for 5 ns;
    clk <= '1';
    wait for 5 ns;
    clk <= '0';
    WR_bank <= '1';
    wait for 5 ns;
    clk <= '1';
    wait for 5 ns;
    clk <= '0';
    WR_bank <= '0';

    -- ADD R0, R0, R2
    op_in <= "00";
    reg_0_id <= "000";
    reg_1_id <= "010";
    wait for 5 ns;
    clk <= '1';
    wait for 5 ns;
    clk <= '0';
    WR_bank <= '1';
    wait for 5 ns;
    clk <= '1';
    wait for 5 ns;
    clk <= '0';
    WR_bank <= '0';

    -- MOV R7, #7
    op_in <= "11";
    reg_0_id <= "111";
    reg_1_id <= "111";
    wait for 5 ns;
    clk <= '1';
    wait for 5 ns;
    clk <= '0';
    WR_bank <= '1';
    wait for 5 ns;
    clk <= '1';
    wait for 5 ns;
    clk <= '0';
    WR_bank <= '0';
    
    --SUB R0, R0, R7
    op_in <= "01";
    reg_0_id <= "000";
    reg_1_id <= "111";
    wait for 5 ns;
    clk <= '1';
    wait for 5 ns;
    clk <= '0';
    WR_bank <= '1';
    wait for 5 ns;
    clk <= '1';
    wait for 5 ns;
    clk <= '0';
    WR_bank <= '0';
    wait for 5 ns;
    wait;
  end process;
end architecture;
--------------------------------------------------------------------------------------

--II. Processeur v1
-- Exemple de programmation
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity proc_v1_test is
end entity;

architecture arch_proc_v1_test of proc_v1_test is
  signal instr : STD_LOGIC_VECTOR(7 downto 0);
  signal rst, clk, Init: STD_LOGIC;

begin
  proc: entity work.proc_v1
    port map(instr, Init, rst, clk);

  process
  begin
    -- Initialize all registers to 0
    rst <= '0';
    clk <= '0';
    Init <= '0';
    wait for 5 ns;
    rst <= '1';
    Init <= '1';

    --MOV R0, #4
    instr <= "11000100";
    wait for 5 ns;
    clk <= '1';
    wait for 5 ns;
    clk <= '0';
    wait for 5 ns;
    clk <= '1';
    wait for 5 ns;
    clk <= '0';

    --MOV R2, #3
    instr <= "11010011";
    wait for 5 ns;
    clk <= '1';
    wait for 5 ns;
    clk <= '0';
    wait for 5 ns;
    clk <= '1';
    wait for 5 ns;
    clk <= '0';

    --ADD R0, R0, R2
    instr <= "00000010";
    wait for 5 ns;
    clk <= '1';
    wait for 5 ns;
    clk <= '0';
    wait for 5 ns;
    clk <= '1';
    wait for 5 ns;
    clk <= '0';

    --MOV R7, #7
    instr <= "11111111";
    wait for 5 ns;
    clk <= '1';
    wait for 5 ns;
    clk <= '0';
    wait for 5 ns;
    clk <= '1';
    wait for 5 ns;
    clk <= '0';

    --SUB R0, R0, R7
    instr <= "01000111";
    wait for 5 ns;
    clk <= '1';
    wait for 5 ns;
    clk <= '0';
    wait for 5 ns;
    clk <= '1';
    wait for 5 ns;
    clk <= '0';


    --AND R7, R7, R2
    instr <= "10111010";
    wait for 5 ns;
    clk <= '1';
    wait for 5 ns;
    clk <= '0';
    wait for 5 ns;
    clk <= '1';
    wait for 5 ns;
    clk <= '0';

    wait;
  end process;
end architecture;


--3+2
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity calcul_1 is
end entity;

architecture arch_calcul_1 of calcul_1 is
signal rst, clk, Init: STD_LOGIC;
signal op_in: STD_LOGIC_VECTOR(1 downto 0);
signal reg0_in, reg1_in: STD_LOGIC_VECTOR(2 downto 0);
signal instr: STD_LOGIC_VECTOR(7 downto 0);

begin
  instr <= op_in & reg0_in & reg1_in;
  proc: entity work.proc_v1
    port map(instr, Init, rst, clk);

  process
  begin
  
   rst <= '0';
   clk <= '0';
   Init <= '0';
   wait for 5 ns;
   rst <= '1';
   Init <= '1';


  op_in <= "11";
  reg0_in <= "000";
  reg1_in <= "011";
  wait for 5 ns;

  clk <= '1';
  wait for 5 ns;
  clk <= '0';
  wait for 5 ns;
  clk <= '1';
  wait for 5 ns;
  clk <= '0'; 
  wait for 5 ns;

  reg0_in <= "001";
  reg1_in <= "010";
  wait for 5 ns;

  clk <= '1';
  wait for 5 ns;
  clk <= '0';
  wait for 5 ns;
  clk <= '1';
  wait for 5 ns;
  clk <= '0';
  wait for 5 ns;

  op_in <= "00";
  reg0_in <= "000";
  reg1_in <= "001";
  wait for 5 ns;

  clk <= '1';
  wait for 5 ns;
  clk <= '0';
  wait for 5 ns;
  clk <= '1';
  wait for 5 ns;
  clk <= '0';
  wait for 5 ns;
  clk <= '1';
  wait for 5 ns;
  clk <= '0';
  wait for 5 ns;

  wait;
  end process;
end architecture;
   

--5+(3-2)
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity calcul_2 is
end entity;

architecture arch_calcul_2 of calcul_2 is
signal rst, clk, Init: STD_LOGIC;
signal op_in: STD_LOGIC_VECTOR(1 downto 0);
signal reg0_in, reg1_in: STD_LOGIC_VECTOR(2 downto 0);
signal instr: STD_LOGIC_VECTOR(7 downto 0);

begin
  instr <= op_in & reg0_in & reg1_in;
  proc: entity work.proc_v1
    port map(instr, Init, rst, clk);

  process
  begin
  
   rst <= '0';
   clk <= '0';
   Init <= '0';
   wait for 5 ns;
   rst <= '1';
   Init <= '1';

   op_in <= "11";
		reg0_in <= "000";
		reg1_in <= "011";
		wait for 5 ns;

		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;
		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;

		reg0_in <= "001";
		reg1_in <= "010";
		wait for 5 ns;

		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;
		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;

		op_in <= "01";
		reg0_in <= "000";
		reg1_in <= "001";
		wait for 5 ns;

		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;
		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;

		op_in <= "11";
		reg0_in <= "001";
		reg1_in <= "101";
		wait for 5 ns;

		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;
		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;

		op_in <= "00";
		reg0_in <= "000";
		reg1_in <= "001";
		wait for 5 ns;

		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;
		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;
		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;

		wait;
	end process;
end architecture;


--6 and 2
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity calcul_3 is
end entity;

architecture arch_calcul_3 of calcul_3 is
signal rst, clk, Init: STD_LOGIC;
signal op_in: STD_LOGIC_VECTOR(1 downto 0);
signal reg0_in, reg1_in: STD_LOGIC_VECTOR(2 downto 0);
signal instr: STD_LOGIC_VECTOR(7 downto 0);

begin
  instr <= op_in & reg0_in & reg1_in;
  proc: entity work.proc_v1
    port map(instr, Init, rst, clk);

  process
  begin
  
   rst <= '0';
   clk <= '0';
   Init <= '0';
   wait for 5 ns;
   rst <= '1';
   Init <= '1';

  op_in <= "11";
		reg0_in <= "000";
		reg1_in <= "011";
		wait for 5 ns;

		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;
		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;


		reg0_in <= "001";
		reg1_in <= "010";
		wait for 5 ns;

		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;
		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;


		op_in <= "10";
		reg0_in <= "000";
		reg1_in <= "001";
		wait for 5 ns;

		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;
		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;
		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;

		wait;
	end process;
end architecture;

--10 + 5 - 2 + 12
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity calcul_4 is
end entity;

architecture arch_calcul_4 of calcul_4 is
signal rst, clk, Init: STD_LOGIC;
signal op_in: STD_LOGIC_VECTOR(1 downto 0);
signal reg0_in, reg1_in: STD_LOGIC_VECTOR(2 downto 0);
signal instr: STD_LOGIC_VECTOR(7 downto 0);

begin
  instr <= op_in & reg0_in & reg1_in;
  proc: entity work.proc_v1
    port map(instr, Init, rst, clk);

  process
  begin
  
   rst <= '0';
   clk <= '0';
   Init <= '0';
   wait for 5 ns;
   rst <= '1';
   Init <= '1';

   init <= '0';
		init <= '1';
		rst <= '1';

	
		op_in <= "11";
		reg0_in <= "000";
		reg1_in <= "101";
		wait for 5 ns;

		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;
		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;

	
		reg0_in <= "001";
		wait for 5 ns;

		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;
		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;


		op_in <= "00";
		reg0_in <= "000";
		reg1_in <= "001";
		wait for 5 ns;

		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;
		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;



		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;
		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;

	
		op_in <= "11";
		reg0_in <= "001";
		reg1_in <= "010";
		wait for 5 ns;

		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;
		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;


		op_in <= "01";
		reg0_in <= "000";
		reg1_in <= "001";
		wait for 5 ns;

		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;
		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;


		op_in <= "11";
		reg0_in <= "001";
		reg1_in <= "110";
		wait for 5 ns;

		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;
		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;


		reg0_in <= "010";
		wait for 5 ns;

		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;
		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;


		op_in <= "00";
		reg0_in <= "001";
		reg1_in <= "010";
		wait for 5 ns;

		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;
		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;


		op_in <= "00";
		reg0_in <= "000";
		reg1_in <= "001";
		wait for 5 ns;

		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;
		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;
		clk <= '1';
		wait for 5 ns;
		clk <= '0';
		wait for 5 ns;

		wait;
	end process;
end architecture;
