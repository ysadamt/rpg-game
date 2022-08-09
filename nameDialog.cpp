#include "nameDialog.h"

// event table for "OK" and "Cancel" buttons
wxBEGIN_EVENT_TABLE(nameDialog, wxDialog)
	EVT_BUTTON(10004, setOK)
	EVT_BUTTON(10005, setCancel)
wxEND_EVENT_TABLE()

const std::string& nameDialog::getName() const
{
	return m_name;
}

void nameDialog::setCancel(wxCommandEvent& evt)
{
	this->EndModal(0);	// closes dialog box, returning 0 to ShowModal()
}

void nameDialog::setOK(wxCommandEvent& evt)
{
	if (static_cast<std::string>(m_nameInput->GetLineText(0)) == "")
	{
		m_name = "Player";	// if no name provided, set name to Player
	}
	else
	{
		/* get input from line 0 (first line) of text, convert to string */
		m_name = static_cast<std::string>(m_nameInput->GetLineText(0));
	}
	this->EndModal(1);	// closes dialog box, returning 1 to ShowModal()
}