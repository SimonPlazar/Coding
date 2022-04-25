package demoProject;


import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class demo {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		File f = new File("C:\\IMDB_date_name_full_sorted.list");
		BufferedReader b = new BufferedReader(new FileReader(f));
		String readLine = "";
		System.out.println("Reading file using Buffered Reader");

		readLine = b.readLine();
		int N = Integer.parseInt(readLine);

		for (int i = 0; i < N; i++) {
			readLine = b.readLine();
			if (readLine.isBlank())
				continue;
			
			String datumString = readLine.substring(0, 8);
			String ime = readLine.substring(9);
			int datum = Integer.parseInt(datumString);
			System.out.println(datum);
			// VSTAVI_V_DREVO(datum,ime);
		}
	}
}


