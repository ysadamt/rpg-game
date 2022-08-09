#ifndef CMAIN_H
#define CMAIN_H

#include "wx/wx.h"
#include "Creature.h"
#include "Player.h"
#include "Monster.h"
#include "Random.h"

class cMain : public wxFrame
{
public:
	cMain() : wxFrame(nullptr, wxID_ANY, "Simple RPG", wxDefaultPosition)
	{
		/* center and color main frame */
		this->Center();
		this->SetBackgroundColour(wxColour(240, 240, 240));

		wxBoxSizer* m_topSizer{ new wxBoxSizer(wxVERTICAL) };       // sizer for wxTextCtrl: output and stat boxes
		wxBoxSizer* m_buttonSizer{ new wxBoxSizer(wxVERTICAL) };    // sizer for wxButton: play button

		/* game output box, acts as a terminal for output */
		m_gameOutput = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(400, 200),
			wxTE_READONLY | wxTE_MULTILINE | wxTE_RICH);
		
		/* stat box, keeps track of member variables (player stats) */
		m_statBox = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 320), wxSize(400, 81),
			wxTE_READONLY | wxTE_MULTILINE | wxTE_NO_VSCROLL);

		/* button to start the game */
		m_playButton = new wxButton(this, 10001, "Play");

		/* text attribute object for bolded words in game output box to use */
		m_bold = new wxTextAttr();
		m_bold->SetFontWeight(wxFONTWEIGHT_BOLD);
		m_bold->SetFontFamily(wxFONTFAMILY_DEFAULT);
		m_bold->SetFontSize(wxFONTSIZE_SMALL);

		/* formatting and sizer stuff */
		m_topSizer->Add(m_gameOutput, 1, wxEXPAND | wxALL, 10);
		m_topSizer->Add(m_statBox, 0, wxEXPAND | wxALL, 10);
		m_buttonSizer->Add(m_playButton, 0, wxALL, 10);

		m_topSizer->Add(m_buttonSizer, 0, wxALIGN_CENTER);
		SetSizerAndFit(m_topSizer);
	}

	~cMain()
	{
		/* prevent memory leaks */
		delete m_gameOutput;
		delete m_statBox;
		delete m_playButton;
		delete m_bold;
	}

public:
	wxTextCtrl* m_gameOutput{ nullptr };
	wxTextCtrl* m_statBox{ nullptr };
	wxButton* m_playButton{ nullptr };
	wxTextAttr* m_bold{ nullptr };

	void startGame(wxCommandEvent& evt);
	void attackPlayer(Player& player, Monster& monster);
	void attackMonster(Player& player, Monster& monster);
	void fightMonster(Player& player, Monster& monster);
	void printStats(Player& player) const;

	wxDECLARE_EVENT_TABLE();

};

#endif 