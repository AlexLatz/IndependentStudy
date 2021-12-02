import java.util.InputMismatchException;
import java.util.Scanner;

public class UI {
    private Board board;
    private final Scanner scanner;
    private Minimax minimax;
    public static final String ANSI_RED = "\u001B[31m";
    public static final String ANSI_YELLOW = "\u001B[33m";
    public static final String ANSI_BLUE = "\u001B[34m";
    public static final String ANSI_RESET = "\u001B[0m";

    public UI() {
        this.scanner = new Scanner(System.in);
        startGame();
    }

    public void startGame() {
        System.out.println("Welcome to Connect 4!");
        int rows = -1;
        int cols = -1;
        int choice = -1;
        while (true) {
            System.out.println("How many rows would you like? (Enter 0 for the default: 6, minimum: 4)");
            try {
                rows = scanner.nextInt();
            } catch (final InputMismatchException e) {
                System.out.println("Invalid input. Please enter an integer.");
                scanner.nextLine();
                continue;
            }
            if (rows > 3 || rows == 0)
                break;
            else
                System.out.println("Please enter either 0 or a number greater than 3.");
        }
        while (true) {
            System.out.println("How many columns would you like? (Enter 0 for the default: 7, minimum: 4)");
            try {
                cols = scanner.nextInt();
            } catch (final InputMismatchException e) {
                System.out.println("Invalid input. Please enter an integer.");
                scanner.nextLine();
                continue;
            }
            if (cols > 3 || cols == 0)
                break;
            else
                System.out.println("Please enter either 0 or a number greater than 3.");
        }
        while (true) {
            System.out.println(
                    "Would you like to play against another player or against the computer? (Enter 2 for 2 players or 1 for the computer)");
            try {
                choice = scanner.nextInt();
            } catch (final InputMismatchException e) {
                System.out.println("Invalid input. Please enter either 1 or 2.");
                scanner.nextLine();
                continue;
            }
            if (choice == 1 || choice == 2)
                break;
            else
                System.out.println("Please enter either 1 or 2.");
        }
        if (rows == 0)
            rows = 6;
        if (cols == 0)
            cols = 7;
        gameLoop(rows, cols, choice);
    }

    private void gameLoop(int rows, int cols, int choice) {
        this.board = new Board(rows, cols);
        if (choice == 1)
            minimax = new Minimax(this.board.copy());
        boolean turn = true;
        while (board.getMoves() < rows * cols && board.getWinner() == 0) {
            if (choice == 2) {
                System.out.println("The board:");
                printBoard();
                board.placeMarker(columnSelection(turn ? 1 : 2), turn);
            } else if (turn) {
                System.out.println("The board:");
                printBoard();
                board.placeMarker(columnSelection(1), true);
            } else {
                board.placeMarker(minimax.getMove(board) + 1, false);
            }
            turn = !turn;
        }
        printBoard();
        if (board.getWinner() != 0) {
            if (choice == 1 && board.getWinner() == 2)
                System.out.println("The computer wins!");
            else
                System.out.println("Player " + board.getWinner() + " wins!");
        } else
            System.out.println("The board is full! Game Over");
    }

    private int columnSelection(int playerNum) {
        int col = -1;
        while (true) {
            System.out.println("Player " + playerNum + ": Enter a column number to place your piece.");
            try {
                col = scanner.nextInt();
            } catch (final InputMismatchException e) {
                System.out.println("Invalid input. Please enter a number.");
                scanner.nextLine();
                continue;
            }
            if (col <= board.getCols() && col > 0)
                if (board.getColHeight(col - 1) >= board.getCols()-1)
                    System.out.println("This column is full. Please pick another.");
                else break;
            else
                System.out.println("Please enter a valid column number.");
        }
        return col;
    }

    private void printBoard() {
        final int[][] arr = board.getBoard();
        for (int i = 0; i < arr.length; i++) {
            if (i != 0) {
                System.out.print("├");
                System.out.print(" — ┼".repeat(board.getCols() - 1));
                System.out.print(" — ┤");
            } else {
                for (int j = 1; j <= board.getCols(); j++) {
                    System.out.print("  " + j + " ");
                }
                System.out.println();
                System.out.print(ANSI_BLUE + "┌");
                System.out.print(" — ┬".repeat(board.getCols() - 1));
                System.out.print(" — ┐");
            }
            System.out.println();
            System.out.print("|");
            for (int j = 0; j < board.getCols(); j++) {
                switch (arr[i][j]) {
                case 1:
                    System.out.print(ANSI_RED + " 1" + ANSI_RESET);
                    break;
                case 2:
                    System.out.print(ANSI_YELLOW + " 2" + ANSI_RESET);
                    break;
                default:
                    System.out.print("  ");
                }
                System.out.print(ANSI_BLUE + " |");
            }
            System.out.println();
        }
        System.out.print("└");
        System.out.print(" — ┴".repeat(board.getCols() - 1));
        System.out.print(" — ┘" + ANSI_RESET);
        System.out.println();
    }

    public static void main(String[] args) {
        final UI ui = new UI();
    }
}
