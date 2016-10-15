// URL: https://algospot.com/judge/problem/read/DRAWRECT

package Algorithm;

import java.util.Scanner;

public class Algospot_Drawrect {
	static int[] pos(int[] xy)
	{
		if (xy[0] == xy[1])
			xy[3] = xy[2];
		else if (xy[0] == xy[2])
			xy[3] = xy[1];
		else
			xy[3] = xy[0];
		return xy;
	}
	
	public static void main(String[] args) {

		Scanner reader = new Scanner(System.in);
		int t = reader.nextInt();
		for(int j=0;j<t;j++){
			int[] xpos = new int[4];
			int[] ypos = new int[4];

			for (int i = 0; i < 3; i++) {
				xpos[i] = reader.nextInt();
				ypos[i] = reader.nextInt();
			}

			xpos = pos(xpos);
			ypos = pos(ypos);

			System.out.println(xpos[3] + " " + ypos[3]);
		}
		
	}
}
