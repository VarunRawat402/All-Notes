----------------------------------------------------------------------------------------------------------------------
ARRAYS:
----------------------------------------------------------------------------------------------------------------------

Syntax:
    dataType arrName[] = new dataType[size];

    int marks[] = new int[5];
    int marks[] = {1,2,3,4,5};      //When we dont know the size of the array

Ex:
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int marks[] = new int[3];
        marks[0] = 402;
        marks[1] = 403;
        marks[2] = 404;

        for(int i=0;i<marks.length;i++){
            System.out.println(marks[i]);
        }
    }

----------------------------------------------------------------------------------------------------------------------

2D Arrays:

Syntax:
    dataType arrName[][] = new dataType[rows][col]

    int grid[][] = new int[3][3];

Ex: Take a 2D array as input and print it.

    Scanner sc = new Scanner(System.in);

    System.out.println("Enter the rows and col respectively");
    int rows = sc.nextInt();
    int col = sc.nextInt();

    int grid[][] = new int[rows][col];

    System.out.println("Enter the numbers in the grid");
    for(int i=0;i<rows;i++){
        for(int j=0;j<col;j++){
            grid[i][j] = sc.nextInt();
        }
    }

    for(int i=0;i<rows;i++){
        for(int j=0;j<col;j++){
            System.out.print(grid[i][j]+" ");
        }
        System.out.println();
    }

----------------------------------------------------------------------------------------------------------------------


