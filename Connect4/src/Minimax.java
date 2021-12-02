import java.util.ArrayList;
import java.util.Collections;

public class Minimax {
    //Minimax AI for connect 4 that implements alpha-beta pruning to cut down on search space
    //The heuristic needs work, but it functions well enough that I don't want to redo it
    private static final double[] weight = {10.0, 100.0, 1000.0, 5000.0};
    private Node node;

    private static class Node implements Comparable<Node> {
        private final Board board;
        private double value;
        private ArrayList<Node> children;

        public Node(Board board) {
            this.board = board;
            this.children = null;
        }

        public ArrayList<Node> getChildren() {
            if (this.children != null) return this.children;
            else if (!isTerminal()) {
                final ArrayList<Node> list = new ArrayList<>();
                for (int i = 0; i < board.getCols(); i++) {
                    if (board.getColHeight(i)+1 < board.getRows()) {
                        final Board child = board.copy();
                        child.placeMarker(i+1, board.getMoves() % 2 == 0);
                        list.add(new Node(child));
                    }
                }
                this.children = list;
            }
            return null;
        }

        public boolean isTerminal() {
            return !(board.getMoves() < board.getRows()*board.getCols() && board.getWinner() == 0);
        }

        @Override
        public int compareTo(Node o) {
            return -Double.compare(this.value, o.value);
        }
    }

    public Minimax(Board start) {
        this.node = new Node(start);
        this.node.getChildren();
    }

    public int getMove(Board board) {
        for (final Node child : this.node.getChildren()) {
            if (child.board.getLastMove() == board.getLastMove()) {
                this.node = child;
                break;
            }
        }
        alphaBeta(this.node, 6, Double.NEGATIVE_INFINITY, Double.POSITIVE_INFINITY, true);
        this.node.getChildren();
        for (final Node child : this.node.getChildren()) {
            final double eval = heuristic(child.board, true);
            if (eval != 0) child.value = eval;
        }
        Collections.sort(this.node.getChildren());
        this.node = this.node.getChildren().get(0);
        return this.node.board.getLastMove();
    }

    public double alphaBeta(Node node, int depth, double alpha, double beta, boolean maximizing) {
        if (depth == 0 || node.isTerminal()) return heuristic(node.board, false);
        if (maximizing) {
            node.getChildren();
            node.value = Double.NEGATIVE_INFINITY;
            for (final Node child : node.getChildren()) {
                node.value = Math.max(node.value, alphaBeta(child, depth-1, alpha, beta, false));
                alpha = Math.max(alpha, node.value);
                if (alpha >= beta) break;
            }
        } else {
            node.value = Double.POSITIVE_INFINITY;
            node.getChildren();
            for (final Node child : node.getChildren()) {
                node.value = Math.min(node.value, alphaBeta(child, depth-1, alpha, beta, true));
                beta = Math.min(beta, node.value);
                if (beta <= alpha) break;
            }
        }
        return node.value;
    }

    private static double heuristic(Board board, boolean endgame) {
        final int[][] arr = board.getBoard();
        if (!endgame && board.getWinner() == 0 && board.getMoves() < board.getCols()*board.getRows()) {
            double heuristic = 0.0;
            heuristic += numInRow(1, board, arr);
            heuristic += numInRow(2, board, arr);
            heuristic += numInRow(3, board, arr);
            heuristic += numInRow(4, board, arr);
            return heuristic;
        } else if (board.getWinner() == 2) return Double.POSITIVE_INFINITY;
        else if (board.getWinner() == 1) return Double.NEGATIVE_INFINITY;
        else return 0;
    }

    private static double numInRow(int num, Board board, int[][] arr) {
        //Not actually the best way to get number in a row, but the heuristic really doesn't have to be that good
        //In future, should probably use MCTS or make a better heuristic
        double sum = 0;
        for (int i = 0; i < board.getRows(); i++) {
            for (int j = 0; j < board.getCols(); j++) {
                sum += calculateHorizontal(board, arr, i, j, num);
                sum += calculateVertical(board, arr, i, j, num);
                sum += calculateDiagonal(board, arr, i, j, num);
            }
        }
        return sum;
    }

    private static double calculateHorizontal(Board board, int[][] arr, int row, int col, int num) {
        double result = 0;
        int sum = 0;
        boolean found = false;
        for (int i = Math.max(col -(num-1), 0); i < Math.min(col + num, board.getCols()); i++) {
            if (arr[row][i] == arr[row][col]) sum++;
            else if (num == 4 && sum == 3 && i + 1 < board.getCols() && arr[row][i+1] == 0 && board.getColHeight(i+1) == row-1) {
                result += arr[row][col] == 1 ? -Minimax.weight[3] : Minimax.weight[3];
                found = true;
            } else sum = 0;
            if (!found && sum >= num) {
                result += arr[row][col] == 1 ? -Minimax.weight[num-1] : Minimax.weight[num-1];
                found = true;
            }
        }
        return result;
    }

    private static double calculateVertical(Board board, int[][] arr, int row, int col, int num) {
        double result = 0;
        int sum = 0;
        boolean found = false;
        for (int i = Math.max(row - (num - 1), 0); i < Math.min(row + num, board.getRows()); i++) {
            if (arr[i][col] == arr[row][col]) sum++;
            else if (num == 4 && sum == 3 && i-1 >= 0 && arr[i-1][col] == 0) {
                result += arr[row][col] == 1 ? -Minimax.weight[3] : Minimax.weight[3];
                found = true;
            } else sum = 0;
            if (!found && sum >= num) {
                result += arr[row][col] == 1 ? -Minimax.weight[num-1] : Minimax.weight[num-1];
                found = true;
            }
        }
        return result;
    }

    private static double calculateDiagonal(Board board, int[][] arr, int row, int col, int num) {
        double result = 0;
        boolean found = false;
        //bottom left -> top right
        int sum = 0;
        for (int i = -(num - 1); i <= (num - 1); i++) {
            if (row + i < 0 || col + i < 0) continue;
            else if (row + i >= board.getRows() || col + i >= board.getCols()) break;
            if (arr[row + i][col + i] == arr[row][col]) {
                sum++;
            } else if (num == 4 && sum == 3 && col + i + 1 < board.getCols() && board.getColHeight(col + i + 1) == row + i) {
                result += arr[row][col] == 1 ? -Minimax.weight[3] : Minimax.weight[3];
                found = true;
            } else sum = 0;
            if (!found && sum >= num) {
                result += arr[row][col] == 1 ? -Minimax.weight[num-1] : Minimax.weight[num-1];
                found = true;
            }
        }
        //bottom right -> top left
        sum = 0;
        found = false;
        for (int i = -(num - 1); i <= (num - 1); i++) {
            if (row + i < 0 || col - i >= board.getCols()) continue;
            else if (row + i >= board.getRows() || col - i < 0) break;
            if (arr[row + i][col - i] == arr[row][col]) {
                sum++;
            } else if (num == 4 && sum == 3 && col - i - 1 >= 0 && board.getColHeight(col - i - 1) == row + i) {
                result += arr[row][col] == 1 ? -Minimax.weight[3] : Minimax.weight[3];
                found = true;
            } else sum = 0;
            if (!found && sum >= num) {
                result += arr[row][col] == 1 ? -Minimax.weight[num-1] : Minimax.weight[num-1];
                found = true;
            }
        }
        return result;
    }

}
