string line;
vector<string> fields;

while (getline(myFile, line)) {

	//need to flush the vector after every loop...
	//otherwise the next line gets mixed with the previous.
	fields.clear();

	//ignore comment lines.
	if (line[0] == '/') {
		continue;
	}

	//start with a single empty string in the vector.
	fields.push_back("");

	//need to record whether we are parsing inside quotes.
	//this prevents commas inside quotes being read incorrectly as syntax.
	bool insideQuotes = false;
	int recordIdx = 0;

	//iterate over the line - char by char.
	for (unsigned int i = 0; i < line.length(); i++) {

		//if we encounter a comma, check if we are inside quotes...
		//if so, continue and treat the comma as a regular character...
		//if not, the comma is part of the CSV file syntax, need to start next field.
		if (line[i] == ',' && !insideQuotes) {
			//go to next record
			fields.push_back("");
			recordIdx++;
			continue;
		}

		//check for quote, set flag accordingly, and continue.
		if (line[i] == '"') {
			insideQuotes = !insideQuotes;
			continue;
		}

		//push data chars into their field string.
		fields[recordIdx].push_back(line[i]);
	}

	//some fields are empty, we need to exclude them.
	//search for empty strings and remove them.
	//the <= 1 condition is needed because strings have a null char at the end...
	//meaning a string that appears empty actually has a length of 1.
	if (fields[fields.size() - 1].length() <= 1) {
		fields.pop_back();
	}

	//for every field - remove leading and trailing whitespace.
	for (unsigned int i = 0; i < fields.size(); i++) {
		fields[i] = trim(fields[i]);
	}

	//call customer constructor with the fields vector.
	//the constructor uses this to create a Customer object which is pushed...
	//into the customerData vector for storage, and so the program can use it later.
	//EXAMPLE: customerData.push_back(Customer(fields));
	//need to do something with the vector here to avoid data being overwritten.
}
