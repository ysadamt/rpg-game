#ifndef CHOICEDIALOG_H
#define CHOICEDIALOG_H

#include "cMain.h"

class choiceDialog : public wxDialog
{
private:
	char m_choice{};	// store user choice

public:
	choiceDialog() : wxDialog(nullptr, wxID_ANY, "Choose", wxPoint(890, 565), wxSize(200, 100))
	{

		/* sizers */
		wxBoxSizer* m_topSizer{ new wxBoxSizer(wxHORIZONTAL) };
		wxBoxSizer* m_buttonSizer{ new wxBoxSizer(wxHORIZONTAL) };

		m_fightButton = new wxButton(this, 10002, "Fight");
		m_runButton = new wxButton(this, 10003, "Run");

		m_buttonSizer->Add(m_fightButton, 0, wxALL, 10);
		m_buttonSizer->Add(m_runButton, 0, wxALL, 10);

		m_topSizer->Add(m_buttonSizer, 0, wxALIGN_CENTER);

		SetSizerAndFit(m_topSizer);
	}

	~choiceDialog()
	{
		/* prevent memory leaks */
		delete m_fightButton;
		delete m_runButton;
	}

public:
	wxButton* m_fightButton{ nullptr };
	wxButton* m_runButton{ nullptr };

	char getChoice() const;
	void setFight(wxCommandEvent& evt);
	void setRun(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

#endif