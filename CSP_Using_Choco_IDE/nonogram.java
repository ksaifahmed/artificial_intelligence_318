import org.chocosolver.solver.Model;
import org.chocosolver.solver.Solver;
import org.chocosolver.solver.variables.IntVar;


public class Nonogram {
public static void main(String[] args) {


int i, j, k;
int[] row_con = {2, 5, 5, 3, 1};
int[] col_con = {2, 4, 4, 4, 2};


// 1. Create a Model
Model model = new Model("my first nonogram problem");
// 2. Create variables



/* the board which is 9 X 9 */
/* (0, 0) is the top left position and (8, 8) is the bottom right position */
/*each cell is an integer variable taking their value in [1, 9] */
IntVar[][] bd = model.intVarMatrix("bd", 5, 5, 0, 1);


 /* the nine rows */
 /* each row is an array of 9 integer variables taking their value in [1, 9] */
IntVar[] r0 = model.intVarArray("r0", 5, 0, 1);
IntVar[] r1 = model.intVarArray("r1", 5, 0, 1);
IntVar[] r2 = model.intVarArray("r2", 5, 0, 1);
IntVar[] r3 = model.intVarArray("r3", 5, 0, 1);
IntVar[] r4 = model.intVarArray("r4", 5, 0, 1);


/* the nine columns */
/* each column is an array of 9 integer variables taking their value in [1, 9] */

IntVar[] c0 = model.intVarArray("c0", 5, 0, 1);
IntVar[] c1 = model.intVarArray("c1", 5, 0, 1);
IntVar[] c2 = model.intVarArray("c2", 5, 0, 1);
IntVar[] c3 = model.intVarArray("c3", 5, 0, 1);
IntVar[] c4 = model.intVarArray("c4", 5, 0, 1);


// 3. Post constraints



    
/* for the nine row variables */
/* each row variable is associated with appropriate cell positions in board */
    
for ( j = 0; j < 5; j++)
  model.arithm (bd[0][j], "=", r0[j]).post();
  
for ( j = 0; j < 5; j++)
  model.arithm (bd[1][j], "=", r1[j]).post();
    
for ( j = 0; j < 5; j++)
  model.arithm (bd[2][j], "=", r2[j]).post();

for ( j = 0; j < 5; j++)
  model.arithm (bd[3][j], "=", r3[j]).post();
  
for ( j = 0; j < 5; j++)
  model.arithm (bd[4][j], "=", r4[j]).post();



/* for the nine column variables */
/* each column variable is associated with appropriate cell positions in board */


for ( i = 0; i < 5; i++)
  model.arithm (bd[i][0], "=", c0[i]).post();

for ( i = 0; i < 5; i++)
  model.arithm (bd[i][1], "=", c1[i]).post();

for ( i = 0; i < 5; i++)
  model.arithm (bd[i][2], "=", c2[i]).post();

for ( i = 0; i < 5; i++)
  model.arithm (bd[i][3], "=", c3[i]).post();

for ( i = 0; i < 5; i++)
  model.arithm (bd[i][4], "=", c4[i]).post();



// post global constraints
model.sum(new IntVar[]{r0[0], r0[1], r0[2], r0[3], r0[4]}, "=", row_con[0]).post();
model.sum(new IntVar[]{r1[0], r1[1], r1[2], r1[3], r1[4]}, "=", row_con[1]).post();
model.sum(new IntVar[]{r2[0], r2[1], r2[2], r2[3], r2[4]}, "=", row_con[2]).post();
model.sum(new IntVar[]{r3[0], r3[1], r3[2], r3[3], r3[4]}, "=", row_con[3]).post();
model.sum(new IntVar[]{r4[0], r4[1], r4[2], r4[3], r4[4]}, "=", row_con[4]).post();


model.sum(new IntVar[]{c0[0], c0[1], c0[2], c0[3], c0[4]}, "=", col_con[0]).post();
model.sum(new IntVar[]{c1[0], c1[1], c1[2], c1[3], c1[4]}, "=", col_con[1]).post();
model.sum(new IntVar[]{c2[0], c2[1], c2[2], c2[3], c2[4]}, "=", col_con[2]).post();
model.sum(new IntVar[]{c3[0], c3[1], c3[2], c3[3], c3[4]}, "=", col_con[3]).post();
model.sum(new IntVar[]{c4[0], c4[1], c4[2], c4[3], c4[4]}, "=", col_con[4]).post();



// 4. Solve the problem




Solver solver = model.getSolver();

solver.showStatistics();
solver.showSolutions();
solver.findSolution();


// 5. Print the solution
for ( i = 0; i < 5; i++){
    for ( j = 0; j < 5; j++){ 
      
            System.out.print(" "); 
            /* get the value for the board position [i][j] for the solved board */
            k = bd [i][j].getValue();
            System.out.print(k );
    }
    System.out.println();
}


}

}
