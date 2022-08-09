#ifndef NAMEDIALOG_H
#define NAMEDIALOG_H

#include "cMain.h"
#include <string>

class nameDialog : public wxDialog
{
private:
	std::string m_name{};

public:
	nameDialog() : wxDialog(nullptr, wxID_ANY, "Enter your name", wxDefaultPosition, wxSize(300, 50))
	{
		wxBoxSizer* m_topSizer{ new wxBoxSizer(wxVERTICAL) };       // sizer for wxTextCtrl: name input box
		wxBoxSizer* m_buttonSizer{ new wxBoxSizer(wxHORIZONTAL) };    // sizer for wxButton: ok and cancel button

		m_okButton = new wxButton(this, 10004, "OK");
		m_cancelButton = new wxButton(this, 10005, "Cancel");
		m_nameInput = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 10), wxSize(200, 20));

		m_topSizer->Add(m_nameInput, 1, wxEXPAND | wxALL, 10);
		m_buttonSizer->Add(m_okButton, 0, wxALL, 10);
		m_buttonSizer->Add(m_cancelButton, 0, wxALL, 10);

		m_topSizer->Add(m_buttonSizer, 0, wxALIGN_CENTER);
		SetSizerAndFit(m_topSizer);

		this->Center();	// center this dialog
	}

	~nameDialog()
	{
		/* prevent memory leaks */
		delete m_nameInput;
		delete m_cancelButton;
		delete m_okButton;
	}

public:
	wxTextCtrl* m_nameInput{ nullptr };
	wxButton* m_cancelButton{ nullptr };
	wxButton* m_okButton{ nullptr };

	void setOK(wxCommandEvent& evt);
	void setCancel(wxCommandEvent& evt);
	const std::string& getName() const;

	wxDECLARE_EVENT_TABLE();
};

#endif

