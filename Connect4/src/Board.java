public class Board {
    // 1 for player 1, 2 for player 2, 0 for empty
    private final int[][] board;
    private int winner;
    private final int[] colHeight;
    private int moves;
    private int lastMove;

    public Board(int rows, int cols) {
        if (rows < 4 || cols < 4)
            throw new IllegalArgumentException("The board must be at least 4x4");
        this.board = new int[rows][cols];
        this.colHeight = new int[cols];
        this.moves = 0;
        this.winner = 0;
    }

    public Board(int[][] board, int[] colHeight, int winner, int moves, int lastMove) {
        this.board = board;
        this.colHeight = colHeight;
        this.winner = winner;
        this.moves = moves;
        this.lastMove = lastMove;
    }

    public void placeMarker(int col, boolean player1) {
        col = col - 1;
        if (moves > getRows() * getCols())
            throw new IndexOutOfBoundsException("There are no more available spaces");
        if (colHeight[col] >= getRows())
            throw new IndexOutOfBoundsException("This column is full");
        final int height = getRows() - 1 - colHeight[col]++;
        this.board[height][col] = (byte) (player1 ? 1 : 2);
        lastMove = col;
        moves++;
        checkWinner(height, col);
    }

    public int[][] getBoard() {
        // defensive copy for safety
        final int[][] copy = new int[getRows()][getCols()];
        for (int i = 0; i < getRows(); i++) {
            System.arraycopy(this.board[i], 0, copy[i], 0, getCols());
        }
        return copy;
    }

    public int getCols() {
        return this.board[0].length;
    }

    public int getRows() {
        return this.board.length;
    }

    public int getMoves() {
        return this.moves;
    }

    public int getWinner() {
        return this.winner;
    }

    public int getLastMove() {
        return this.lastMove;
    }

    public int getColHeight(int i) {
        return colHeight[i];
    }

    public Board copy() {
        final int[][] newBoard = new int[getRows()][getCols()];
        final int[] newColHeight = new int[getCols()];
        for (int i = 0; i < board.length; i++) {
            System.arraycopy(board[i], 0, newBoard[i], 0, getCols());
        }
        System.arraycopy(colHeight, 0, newColHeight, 0, colHeight.length);
        return new Board(newBoard, newColHeight, winner, moves, lastMove);
    }

    private void checkWinner(int row, int col) {
        if (checkHorizontal(row, col) || checkVertical(row, col) || checkDiagonal(row, col)) {
            winner = board[row][col];
        }
    }

    private boolean checkHorizontal(int row, int col) {
        int sum = 0;
        for (int i = Math.max(col - 3, 0); i < Math.min(col + 4, getCols()); i++) {
            if (board[row][i] == board[row][col])
                sum++;
            else
                sum = 0;
            if (sum >= 4)
                return true;
        }
        return false;
    }

    private boolean checkVertical(int row, int col) {
        int sum = 0;
        for (int i = Math.max(row - 3, 0); i < Math.min(row + 4, getRows()); i++) {
            if (board[i][col] == board[row][col])
                sum++;
            else
                sum = 0;
            if (sum >= 4)
                return true;
        }
        return false;
    }

    private boolean checkDiagonal(int row, int col) {
        // bottom left -> top right
        int sum = 0;
        for (int i = -3; i <= 3; i++) {
            if (row + i < 0 || col + i < 0)
                continue;
            else if (row + i >= getRows() || col + i >= getCols())
                break;
            if (board[row + i][col + i] == board[row][col])
                sum++;
            else
                sum = 0;
            if (sum >= 4)
                return true;
        }
        // bottom right -> top left
        sum = 0;
        for (int i = -3; i <= 3; i++) {
            if (row + i < 0 || col - i >= getCols())
                continue;
            else if (row + i >= getRows() || col - i < 0)
                break;
            if (board[row + i][col - i] == board[row][col])
                sum++;
            else
                sum = 0;
            if (sum >= 4)
                return true;
        }
        return false;
    }
}