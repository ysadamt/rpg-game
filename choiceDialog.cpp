#include "choiceDialog.h"

// event table for "Fight" and "Run" buttons
wxBEGIN_EVENT_TABLE(choiceDialog, wxDialog)
	EVT_BUTTON(10002, setFight)
	EVT_BUTTON(10003, setRun)
wxEND_EVENT_TABLE()

char choiceDialog::getChoice() const
{
	return m_choice;
}

void choiceDialog::setFight(wxCommandEvent& evt)
{
	m_choice = 'f';		// player clicks fight button
	this->EndModal(1);	// closes dialog box
}

void choiceDialog::setRun(wxCommandEvent& evt)
{
	m_choice = 'r';		// player clicks run button
	this->EndModal(0);	// closes dialog box
}