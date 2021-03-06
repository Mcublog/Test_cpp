// TestFunc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "pdf/pdfgen.h"


using namespace std;


int main() {

	struct pdf_info info = {
			"My software",// .creator =
			"My software",// .producer = 
			"My document",// .title = 
			"My name",// .author = 
			"My subject",// .subject = 
			"Today"// .date = 
	};
	struct pdf_doc* pdf = pdf_create(PDF_A4_WIDTH, PDF_A4_HEIGHT, &info);
	pdf_set_font(pdf, "Times-Roman");
	pdf_append_page(pdf);
	pdf_add_text(pdf, NULL, "This is text", 12, 50, 20, PDF_BLACK);
	pdf_add_line(pdf, NULL, 50, 24, 150, 24, 1, PDF_GREEN);
	pdf_save(pdf, "output.pdf");
	pdf_destroy(pdf);

    system("pause");
    return 0;
}
