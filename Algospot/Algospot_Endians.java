// URL: https://algospot.com/judge/problem/read/ENDIANS

package Algorithm;

import java.util.Scanner;

// Á¶°Ç: 32bit 00000000 00000000 00000000 00000000
public class Algospot_Endians {
	public static void main(String[] args) {
		Scanner reader = new Scanner(System.in); // Reading from System.in
		int c = reader.nextInt();

		for (int i = 0; i < c; i++) {
			long num = reader.nextInt();
			long result = ((num & (255 << 24)) >> 24) + ((num & (255 << 16)) >> 8) + ((num & (255 << 8)) << 8)
					+ ((num & 255) << 24);
			System.out.println(result);
		}
	}
}
